// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "../include/get_world_region_details_command.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

void protobuf_ShutdownFile_get_5fworld_5fregion_5fdetails_5fcommand_2eproto() {
  delete DF_get_world_region_details_command::default_instance_;
}

void protobuf_AddDesc_get_5fworld_5fregion_5fdetails_5fcommand_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  DF_get_world_region_details_command::default_instance_ = new DF_get_world_region_details_command();
  DF_get_world_region_details_command::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_get_5fworld_5fregion_5fdetails_5fcommand_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_get_5fworld_5fregion_5fdetails_5fcommand_2eproto {
  StaticDescriptorInitializer_get_5fworld_5fregion_5fdetails_5fcommand_2eproto() {
    protobuf_AddDesc_get_5fworld_5fregion_5fdetails_5fcommand_2eproto();
  }
} static_descriptor_initializer_get_5fworld_5fregion_5fdetails_5fcommand_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int DF_get_world_region_details_command::kWorldPosXFieldNumber;
const int DF_get_world_region_details_command::kWorldPosYFieldNumber;
#endif  // !_MSC_VER

DF_get_world_region_details_command::DF_get_world_region_details_command()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void DF_get_world_region_details_command::InitAsDefaultInstance() {
}

DF_get_world_region_details_command::DF_get_world_region_details_command(const DF_get_world_region_details_command& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void DF_get_world_region_details_command::SharedCtor() {
  _cached_size_ = 0;
  world_pos_x_ = 0;
  world_pos_y_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DF_get_world_region_details_command::~DF_get_world_region_details_command() {
  SharedDtor();
}

void DF_get_world_region_details_command::SharedDtor() {
  if (this != default_instance_) {
  }
}

void DF_get_world_region_details_command::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const DF_get_world_region_details_command& DF_get_world_region_details_command::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_get_5fworld_5fregion_5fdetails_5fcommand_2eproto();  return *default_instance_;
}

DF_get_world_region_details_command* DF_get_world_region_details_command::default_instance_ = NULL;

DF_get_world_region_details_command* DF_get_world_region_details_command::New() const {
  return new DF_get_world_region_details_command;
}

void DF_get_world_region_details_command::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    world_pos_x_ = 0;
    world_pos_y_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool DF_get_world_region_details_command::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 world_pos_x = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &world_pos_x_)));
          set_has_world_pos_x();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_world_pos_y;
        break;
      }
      
      // required int32 world_pos_y = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_world_pos_y:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &world_pos_y_)));
          set_has_world_pos_y();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void DF_get_world_region_details_command::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 world_pos_x = 1;
  if (has_world_pos_x()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->world_pos_x(), output);
  }
  
  // required int32 world_pos_y = 2;
  if (has_world_pos_y()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->world_pos_y(), output);
  }
  
}

int DF_get_world_region_details_command::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 world_pos_x = 1;
    if (has_world_pos_x()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->world_pos_x());
    }
    
    // required int32 world_pos_y = 2;
    if (has_world_pos_y()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->world_pos_y());
    }
    
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DF_get_world_region_details_command::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const DF_get_world_region_details_command*>(&from));
}

void DF_get_world_region_details_command::MergeFrom(const DF_get_world_region_details_command& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_world_pos_x()) {
      set_world_pos_x(from.world_pos_x());
    }
    if (from.has_world_pos_y()) {
      set_world_pos_y(from.world_pos_y());
    }
  }
}

void DF_get_world_region_details_command::CopyFrom(const DF_get_world_region_details_command& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DF_get_world_region_details_command::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  
  return true;
}

void DF_get_world_region_details_command::Swap(DF_get_world_region_details_command* other) {
  if (other != this) {
    std::swap(world_pos_x_, other->world_pos_x_);
    std::swap(world_pos_y_, other->world_pos_y_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string DF_get_world_region_details_command::GetTypeName() const {
  return "DF_get_world_region_details_command";
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
