#include <typeinfo>

#include "../include/get_world_region_details_command.pb.h"
#include "../include/world_region_details_result.pb.h"


#include <typeinfo>
#include <tinythread.h>
#include <queue>
#include <memory>
#include "../include/dfhack.h"

using namespace std;
using namespace DFHack;

using df::global::ui;
using df::global::world;

DFHACK_PLUGIN("worldregiondetails");
DFHACK_PLUGIN_IS_ENABLED(s_enabled);

static int embark_x_max = -1;
static int embark_y_max = -1;
static int embark_x_min = 9000;
static int embark_y_min = 9000;

static bool embark_rectangle_calculated = false;

//----------------------------------------------------------------------------//
// external functions prototypes
//----------------------------------------------------------------------------//

extern int fill_world_region_details(int world_pos_x,
                                     int world_pos_y
                                    );
extern void delete_world_region_details(df::world_region_details* ptr_world_region_details);


//----------------------------------------------------------------------------//
// External variables
//----------------------------------------------------------------------------//
extern unsigned int fill_world_region_details_address;
extern unsigned int delete_world_region_details_address;

//----------------------------------------------------------------------------//
// local functions prototypes
//----------------------------------------------------------------------------//
command_result get_world_region_details(color_ostream& con,
                                        std::vector <std::string>& parameters
                                       );

command_result get_world_region_details_command(color_ostream& con,
                                                const DF_get_world_region_details_command*, // IN  protobuff message
                                                DF_world_region_details_result*             // OUT protobuff message
                                               );


//----------------------------------------------------------------------------//
// Connect our functions to the RPC server so they can be called
// remotely by the client
//----------------------------------------------------------------------------//
DFhackCExport DFHack::RPCService* plugin_rpcconnect(color_ostream&)
{
    DFHack::RPCService* svc = new DFHack::RPCService();

    svc->addFunction("DF_get_world_region_details",    // RPC Command name
                     get_world_region_details_command  // RPC command object
                    );

    return svc;
}


// -----------------------------------------------------------------
// Here go all the command declarations...
// mostly to allow having the mandatory stuff on top of the file and commands on the bottom
// -----------------------------------------------------------------
command_result world_region_details(color_ostream& con,
                                    std::vector <std::string>& parameters
                                   );


// -----------------------------------------------------------------
// Mandatory init function. If you have some global state, create it here.
// -----------------------------------------------------------------
DFhackCExport command_result plugin_init(color_ostream& con,
                                         std::vector <PluginCommand>& commands
                                        )
{

    uint32_t addr;

    addr = Core::getInstance().vinfo->getAddress("fill_world_region_details");
    fill_world_region_details_address = addr;

    addr = Core::getInstance().vinfo->getAddress("delete_world_region_details");
    delete_world_region_details_address = addr;


    // Fill the command list with your commands.
    commands.push_back(PluginCommand("get_world_region_details",
                                     "Returns a world region details using protocol buffers",
                                     get_world_region_details /*,
                                     true or false - true means that the command
                                     can't be used from non-interactive user interface'*/));
    return CR_OK;
}

// -----------------------------------------------------------------
// This is called right before the plugin library is removed from memory.
// -----------------------------------------------------------------
DFhackCExport command_result plugin_shutdown(color_ostream& con)
{
    return CR_OK;
}

// -----------------------------------------------------------------
// Compute the enclosing rectangle (in world coordinates) of all current
// world region details df::coord2s pos field items in the vector
// Used to quickly discard coordinates outside this rectangle
// -----------------------------------------------------------------
void calculate_current_region_rectangle()
{
    for (unsigned int i = 0; i < world->world_data->region_details.size(); i++)
    {
        df::world_region_details* ptr_wrd = world->world_data->region_details[i];
        auto pos = ptr_wrd->pos;
        if (pos.x < embark_x_min)
            embark_x_min = pos.x;
        if (pos.y < embark_y_min)
            embark_y_min = pos.y;
        if (pos.x > embark_x_max)
            embark_x_max = pos.x;
        if (pos.y > embark_y_max)
            embark_y_max = pos.y;
    }
    embark_rectangle_calculated = true;
}

// -----------------------------------------------------------------
// Checks if a given worid coordinate is inside the world region
// details vector elements
// -----------------------------------------------------------------
bool inside_rectangle(const int p_pos_x, const int p_pos_y)
{
    if (p_pos_x < embark_x_min)
        return false;
    if (p_pos_y < embark_y_min)
        return false;
    if (p_pos_x > embark_x_max)
        return false;
    if (p_pos_y > embark_y_max)
        return false;
    return true;
}


// -----------------------------------------------------------------
// Copy df::world_region_details::T_edges edges field to
// the output protocol buffer message
// -----------------------------------------------------------------
void copy_edges(df::world_region_details*       p_ptr_wrd,
                DF_world_region_details_result* p_out
               )
{
    auto edges = p_out->mutable_edges();

    for (int i = 0; i < 17; i++)
        for (int j = 0; j < 17; j++)
        {
            bool limit_x  = (i > 15);
            bool limit_y  = (j > 15);

            if (!limit_x)
            {
                auto split_x = edges->add_split_x();
                split_x->set_pos_x(p_ptr_wrd->edges.split_x[i][j].x);
                split_x->set_pos_y(p_ptr_wrd->edges.split_x[i][j].y);
            }

            if (!limit_y)
            {
                auto split_y = edges->add_split_y();
                split_y->set_pos_x(p_ptr_wrd->edges.split_y[i][j].x);
                split_y->set_pos_y(p_ptr_wrd->edges.split_y[i][j].y);
            }

            if (!limit_x && !limit_y)
            {
                edges->add_biome_x(p_ptr_wrd->edges.biome_x[i][j]);
                edges->add_biome_y(p_ptr_wrd->edges.biome_y[i][j]);
                edges->add_biome_corner(p_ptr_wrd->edges.biome_corner[i][j]);
            }
        }
}


// -----------------------------------------------------------------
// Copy df::world_region_details horizontal and vertical rivers
// to the output protocol buffer message
// -----------------------------------------------------------------
void copy_rivers(df::world_region_details*       p_ptr_wrd,
                 DF_world_region_details_result* p_out
                )
{
    auto rivers_vertical = p_out->mutable_rivers_vertical();
    auto rivers_horizontal = p_out->mutable_rivers_horizontal();

    for (int i = 0; i < 17; i++)
        for (int j = 0; j < 17; j++)
        {
            bool limit_vertical   = (i > 15);
            bool limit_horizontal = (j > 15);

            if (!limit_vertical)
            {
                rivers_vertical->add_x_min(p_ptr_wrd->rivers_vertical.x_min[i][j]);
                rivers_vertical->add_x_max(p_ptr_wrd->rivers_vertical.x_max[i][j]);
                rivers_vertical->add_active(p_ptr_wrd->rivers_vertical.active[i][j]);
                rivers_vertical->add_elevation(p_ptr_wrd->rivers_vertical.elevation[i][j]);
            }

            if (!limit_horizontal)
            {
                rivers_horizontal->add_y_min(p_ptr_wrd->rivers_horizontal.y_min[i][j]);
                rivers_horizontal->add_y_max(p_ptr_wrd->rivers_horizontal.y_max[i][j]);
                rivers_horizontal->add_active(p_ptr_wrd->rivers_horizontal.active[i][j]);
                rivers_horizontal->add_elevation(p_ptr_wrd->rivers_horizontal.elevation[i][j]);
            }
        }
}


// -----------------------------------------------------------------
// Copy a world region details fields to the output
// protocol buffer message
// -----------------------------------------------------------------
command_result copy_world_region_details(df::world_region_details*       p_ptr_wrd,
                                         DF_world_region_details_result* p_out
                                        )
{
    if (p_ptr_wrd == 0)
        return CR_FAILURE;

    if (p_out == 0)
        return CR_FAILURE;

    for (int i = 0; i < 17; i++)
        for (int j = 0; j < 17; j++)
        {
            p_out->add_biome(p_ptr_wrd->biome[i][j]);
            p_out->add_elevation(p_ptr_wrd->elevation[i][j]);
            if ((i != 16) && (j != 16))
                p_out->add_elevation2(p_ptr_wrd->elevation2[i][j]);

        }

    copy_edges(p_ptr_wrd,
               p_out
              );

    auto pos = p_out->mutable_pos();
    pos->set_pos_x(p_ptr_wrd->pos.x);
    pos->set_pos_y(p_ptr_wrd->pos.y);

    copy_rivers(p_ptr_wrd,
                p_out
               );
    p_out->set_lava_stone(p_ptr_wrd->lava_stone);

    return CR_OK;
}

// -----------------------------------------------------------------
// This is a command called remotely by RPC
// -----------------------------------------------------------------
command_result get_world_region_details_command(color_ostream&                             p_con,
                                                const DF_get_world_region_details_command* p_in,
                                                DF_world_region_details_result*            p_out
                                               )
{
    // Suspend the game during the execution
    // of this funcion
    CoreSuspender suspend;

    // A world must be loaded
    if (df::global::world == nullptr)
        return CR_FAILURE;

    // Get the world coordinates of the region details that we want
    // from the protocol buffers input message
    int pos_x = p_in->world_pos_x();
    int pos_y = p_in->world_pos_y();

    if (world->world_data->region_details.size() > 0)
    {
        // Fortress mode
        if (!embark_rectangle_calculated)
            calculate_current_region_rectangle();

        // Check if the requested world coordinate belongs to the embark area
        if (inside_rectangle(pos_x, pos_y))
        {
            for (unsigned int i = 0; i < world->world_data->region_details.size(); i++)
            {
                df::world_region_details* ptr_wrd = world->world_data->region_details[i];
                if ((ptr_wrd->pos.x == pos_x) && (ptr_wrd->pos.y == pos_y))
                    // Found. Copy it to the protocol buffer output message
                    copy_world_region_details(ptr_wrd,
                                              p_out
                                             );
            }

            // Return not deleting anything
            return CR_OK;

        }
    }

    // The requested coordinate is not in the ones that world_region_details
    // alreday contains

    // Check world region details vector size before insert
    int previous_size = world->world_data->region_details.size();


    // Insert a new world_region_details for the given world coordinates in
    // the vector
    fill_world_region_details(pos_x,
                              pos_y
                             );

    // Check again world region details vector size
    int new_size = world->world_data->region_details.size();

    if (new_size > previous_size)
    {
        // Execution OK.
        // A filled world region details was inserted

        // Get this new world region details
        df::world_region_details* ptr_wrd = world->world_data->region_details[new_size - 1];

        // Copy it to the protocol buffer output message
        copy_world_region_details(ptr_wrd,
                                  p_out
                                 );

        // Delete the created world_region_details
        delete_world_region_details(ptr_wrd);

        // And also delete its entry from world_region_details vector
        world->world_data->region_details.erase(world->world_data->region_details.begin() + new_size - 1);

        // Piece of cake
        return CR_OK;
    }

    // Something happened and was not good
    return CR_FAILURE;
}


// -----------------------------------------------------------------
// This is the console version of the command
// Not needed because the commands are called by RPC
// and not by calling it from the DFHack console
// -----------------------------------------------------------------
command_result get_world_region_details(color_ostream& con,
                                        std::vector <std::string>& parameters
                                       )
{
    return CR_OK;
}
