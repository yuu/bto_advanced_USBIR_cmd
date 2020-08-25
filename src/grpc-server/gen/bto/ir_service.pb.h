// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: bto/ir_service.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_bto_2fir_5fservice_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_bto_2fir_5fservice_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_bto_2fir_5fservice_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_bto_2fir_5fservice_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[5]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_bto_2fir_5fservice_2eproto;
namespace bto {
class DumpRecordResponse;
class DumpRecordResponseDefaultTypeInternal;
extern DumpRecordResponseDefaultTypeInternal _DumpRecordResponse_default_instance_;
class Empty;
class EmptyDefaultTypeInternal;
extern EmptyDefaultTypeInternal _Empty_default_instance_;
class RecStartRequest;
class RecStartRequestDefaultTypeInternal;
extern RecStartRequestDefaultTypeInternal _RecStartRequest_default_instance_;
class Result;
class ResultDefaultTypeInternal;
extern ResultDefaultTypeInternal _Result_default_instance_;
class WriteRequest;
class WriteRequestDefaultTypeInternal;
extern WriteRequestDefaultTypeInternal _WriteRequest_default_instance_;
}  // namespace bto
PROTOBUF_NAMESPACE_OPEN
template<> ::bto::DumpRecordResponse* Arena::CreateMaybeMessage<::bto::DumpRecordResponse>(Arena*);
template<> ::bto::Empty* Arena::CreateMaybeMessage<::bto::Empty>(Arena*);
template<> ::bto::RecStartRequest* Arena::CreateMaybeMessage<::bto::RecStartRequest>(Arena*);
template<> ::bto::Result* Arena::CreateMaybeMessage<::bto::Result>(Arena*);
template<> ::bto::WriteRequest* Arena::CreateMaybeMessage<::bto::WriteRequest>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace bto {

// ===================================================================

class WriteRequest PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:bto.WriteRequest) */ {
 public:
  inline WriteRequest() : WriteRequest(nullptr) {};
  virtual ~WriteRequest();

  WriteRequest(const WriteRequest& from);
  WriteRequest(WriteRequest&& from) noexcept
    : WriteRequest() {
    *this = ::std::move(from);
  }

  inline WriteRequest& operator=(const WriteRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline WriteRequest& operator=(WriteRequest&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const WriteRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const WriteRequest* internal_default_instance() {
    return reinterpret_cast<const WriteRequest*>(
               &_WriteRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(WriteRequest& a, WriteRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(WriteRequest* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(WriteRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WriteRequest* New() const final {
    return CreateMaybeMessage<WriteRequest>(nullptr);
  }

  WriteRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WriteRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WriteRequest& from);
  void MergeFrom(const WriteRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WriteRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "bto.WriteRequest";
  }
  protected:
  explicit WriteRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_bto_2fir_5fservice_2eproto);
    return ::descriptor_table_bto_2fir_5fservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDataFieldNumber = 2,
    kFrequencyFieldNumber = 1,
  };
  // repeated uint32 data = 2;
  int data_size() const;
  private:
  int _internal_data_size() const;
  public:
  void clear_data();
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_data(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      _internal_data() const;
  void _internal_add_data(::PROTOBUF_NAMESPACE_ID::uint32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      _internal_mutable_data();
  public:
  ::PROTOBUF_NAMESPACE_ID::uint32 data(int index) const;
  void set_data(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value);
  void add_data(::PROTOBUF_NAMESPACE_ID::uint32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      data() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_data();

  // int32 frequency = 1;
  void clear_frequency();
  ::PROTOBUF_NAMESPACE_ID::int32 frequency() const;
  void set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_frequency() const;
  void _internal_set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:bto.WriteRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 > data_;
  mutable std::atomic<int> _data_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 frequency_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_bto_2fir_5fservice_2eproto;
};
// -------------------------------------------------------------------

class RecStartRequest PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:bto.RecStartRequest) */ {
 public:
  inline RecStartRequest() : RecStartRequest(nullptr) {};
  virtual ~RecStartRequest();

  RecStartRequest(const RecStartRequest& from);
  RecStartRequest(RecStartRequest&& from) noexcept
    : RecStartRequest() {
    *this = ::std::move(from);
  }

  inline RecStartRequest& operator=(const RecStartRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline RecStartRequest& operator=(RecStartRequest&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const RecStartRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RecStartRequest* internal_default_instance() {
    return reinterpret_cast<const RecStartRequest*>(
               &_RecStartRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(RecStartRequest& a, RecStartRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(RecStartRequest* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RecStartRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline RecStartRequest* New() const final {
    return CreateMaybeMessage<RecStartRequest>(nullptr);
  }

  RecStartRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<RecStartRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const RecStartRequest& from);
  void MergeFrom(const RecStartRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RecStartRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "bto.RecStartRequest";
  }
  protected:
  explicit RecStartRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_bto_2fir_5fservice_2eproto);
    return ::descriptor_table_bto_2fir_5fservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFrequencyFieldNumber = 1,
  };
  // int32 frequency = 1;
  void clear_frequency();
  ::PROTOBUF_NAMESPACE_ID::int32 frequency() const;
  void set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_frequency() const;
  void _internal_set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:bto.RecStartRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::int32 frequency_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_bto_2fir_5fservice_2eproto;
};
// -------------------------------------------------------------------

class Result PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:bto.Result) */ {
 public:
  inline Result() : Result(nullptr) {};
  virtual ~Result();

  Result(const Result& from);
  Result(Result&& from) noexcept
    : Result() {
    *this = ::std::move(from);
  }

  inline Result& operator=(const Result& from) {
    CopyFrom(from);
    return *this;
  }
  inline Result& operator=(Result&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Result& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Result* internal_default_instance() {
    return reinterpret_cast<const Result*>(
               &_Result_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Result& a, Result& b) {
    a.Swap(&b);
  }
  inline void Swap(Result* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Result* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Result* New() const final {
    return CreateMaybeMessage<Result>(nullptr);
  }

  Result* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Result>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Result& from);
  void MergeFrom(const Result& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Result* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "bto.Result";
  }
  protected:
  explicit Result(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_bto_2fir_5fservice_2eproto);
    return ::descriptor_table_bto_2fir_5fservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCodeFieldNumber = 1,
  };
  // int32 code = 1;
  void clear_code();
  ::PROTOBUF_NAMESPACE_ID::int32 code() const;
  void set_code(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_code() const;
  void _internal_set_code(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:bto.Result)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::int32 code_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_bto_2fir_5fservice_2eproto;
};
// -------------------------------------------------------------------

class Empty PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:bto.Empty) */ {
 public:
  inline Empty() : Empty(nullptr) {};
  virtual ~Empty();

  Empty(const Empty& from);
  Empty(Empty&& from) noexcept
    : Empty() {
    *this = ::std::move(from);
  }

  inline Empty& operator=(const Empty& from) {
    CopyFrom(from);
    return *this;
  }
  inline Empty& operator=(Empty&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Empty& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Empty* internal_default_instance() {
    return reinterpret_cast<const Empty*>(
               &_Empty_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(Empty& a, Empty& b) {
    a.Swap(&b);
  }
  inline void Swap(Empty* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Empty* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Empty* New() const final {
    return CreateMaybeMessage<Empty>(nullptr);
  }

  Empty* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Empty>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Empty& from);
  void MergeFrom(const Empty& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Empty* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "bto.Empty";
  }
  protected:
  explicit Empty(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_bto_2fir_5fservice_2eproto);
    return ::descriptor_table_bto_2fir_5fservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:bto.Empty)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_bto_2fir_5fservice_2eproto;
};
// -------------------------------------------------------------------

class DumpRecordResponse PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:bto.DumpRecordResponse) */ {
 public:
  inline DumpRecordResponse() : DumpRecordResponse(nullptr) {};
  virtual ~DumpRecordResponse();

  DumpRecordResponse(const DumpRecordResponse& from);
  DumpRecordResponse(DumpRecordResponse&& from) noexcept
    : DumpRecordResponse() {
    *this = ::std::move(from);
  }

  inline DumpRecordResponse& operator=(const DumpRecordResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline DumpRecordResponse& operator=(DumpRecordResponse&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const DumpRecordResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DumpRecordResponse* internal_default_instance() {
    return reinterpret_cast<const DumpRecordResponse*>(
               &_DumpRecordResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  friend void swap(DumpRecordResponse& a, DumpRecordResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(DumpRecordResponse* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(DumpRecordResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline DumpRecordResponse* New() const final {
    return CreateMaybeMessage<DumpRecordResponse>(nullptr);
  }

  DumpRecordResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<DumpRecordResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const DumpRecordResponse& from);
  void MergeFrom(const DumpRecordResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DumpRecordResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "bto.DumpRecordResponse";
  }
  protected:
  explicit DumpRecordResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_bto_2fir_5fservice_2eproto);
    return ::descriptor_table_bto_2fir_5fservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDataFieldNumber = 1,
  };
  // bytes data = 1;
  void clear_data();
  const std::string& data() const;
  void set_data(const std::string& value);
  void set_data(std::string&& value);
  void set_data(const char* value);
  void set_data(const void* value, size_t size);
  std::string* mutable_data();
  std::string* release_data();
  void set_allocated_data(std::string* data);
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  std::string* unsafe_arena_release_data();
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_data(
      std::string* data);
  private:
  const std::string& _internal_data() const;
  void _internal_set_data(const std::string& value);
  std::string* _internal_mutable_data();
  public:

  // @@protoc_insertion_point(class_scope:bto.DumpRecordResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr data_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_bto_2fir_5fservice_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// WriteRequest

// int32 frequency = 1;
inline void WriteRequest::clear_frequency() {
  frequency_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WriteRequest::_internal_frequency() const {
  return frequency_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 WriteRequest::frequency() const {
  // @@protoc_insertion_point(field_get:bto.WriteRequest.frequency)
  return _internal_frequency();
}
inline void WriteRequest::_internal_set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  frequency_ = value;
}
inline void WriteRequest::set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_frequency(value);
  // @@protoc_insertion_point(field_set:bto.WriteRequest.frequency)
}

// repeated uint32 data = 2;
inline int WriteRequest::_internal_data_size() const {
  return data_.size();
}
inline int WriteRequest::data_size() const {
  return _internal_data_size();
}
inline void WriteRequest::clear_data() {
  data_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 WriteRequest::_internal_data(int index) const {
  return data_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 WriteRequest::data(int index) const {
  // @@protoc_insertion_point(field_get:bto.WriteRequest.data)
  return _internal_data(index);
}
inline void WriteRequest::set_data(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value) {
  data_.Set(index, value);
  // @@protoc_insertion_point(field_set:bto.WriteRequest.data)
}
inline void WriteRequest::_internal_add_data(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  data_.Add(value);
}
inline void WriteRequest::add_data(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_add_data(value);
  // @@protoc_insertion_point(field_add:bto.WriteRequest.data)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
WriteRequest::_internal_data() const {
  return data_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
WriteRequest::data() const {
  // @@protoc_insertion_point(field_list:bto.WriteRequest.data)
  return _internal_data();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
WriteRequest::_internal_mutable_data() {
  return &data_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
WriteRequest::mutable_data() {
  // @@protoc_insertion_point(field_mutable_list:bto.WriteRequest.data)
  return _internal_mutable_data();
}

// -------------------------------------------------------------------

// RecStartRequest

// int32 frequency = 1;
inline void RecStartRequest::clear_frequency() {
  frequency_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 RecStartRequest::_internal_frequency() const {
  return frequency_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 RecStartRequest::frequency() const {
  // @@protoc_insertion_point(field_get:bto.RecStartRequest.frequency)
  return _internal_frequency();
}
inline void RecStartRequest::_internal_set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  frequency_ = value;
}
inline void RecStartRequest::set_frequency(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_frequency(value);
  // @@protoc_insertion_point(field_set:bto.RecStartRequest.frequency)
}

// -------------------------------------------------------------------

// Result

// int32 code = 1;
inline void Result::clear_code() {
  code_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Result::_internal_code() const {
  return code_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Result::code() const {
  // @@protoc_insertion_point(field_get:bto.Result.code)
  return _internal_code();
}
inline void Result::_internal_set_code(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  code_ = value;
}
inline void Result::set_code(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_code(value);
  // @@protoc_insertion_point(field_set:bto.Result.code)
}

// -------------------------------------------------------------------

// Empty

// -------------------------------------------------------------------

// DumpRecordResponse

// bytes data = 1;
inline void DumpRecordResponse::clear_data() {
  data_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline const std::string& DumpRecordResponse::data() const {
  // @@protoc_insertion_point(field_get:bto.DumpRecordResponse.data)
  return _internal_data();
}
inline void DumpRecordResponse::set_data(const std::string& value) {
  _internal_set_data(value);
  // @@protoc_insertion_point(field_set:bto.DumpRecordResponse.data)
}
inline std::string* DumpRecordResponse::mutable_data() {
  // @@protoc_insertion_point(field_mutable:bto.DumpRecordResponse.data)
  return _internal_mutable_data();
}
inline const std::string& DumpRecordResponse::_internal_data() const {
  return data_.Get();
}
inline void DumpRecordResponse::_internal_set_data(const std::string& value) {
  
  data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void DumpRecordResponse::set_data(std::string&& value) {
  
  data_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:bto.DumpRecordResponse.data)
}
inline void DumpRecordResponse::set_data(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:bto.DumpRecordResponse.data)
}
inline void DumpRecordResponse::set_data(const void* value,
    size_t size) {
  
  data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:bto.DumpRecordResponse.data)
}
inline std::string* DumpRecordResponse::_internal_mutable_data() {
  
  return data_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* DumpRecordResponse::release_data() {
  // @@protoc_insertion_point(field_release:bto.DumpRecordResponse.data)
  return data_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void DumpRecordResponse::set_allocated_data(std::string* data) {
  if (data != nullptr) {
    
  } else {
    
  }
  data_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), data,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:bto.DumpRecordResponse.data)
}
inline std::string* DumpRecordResponse::unsafe_arena_release_data() {
  // @@protoc_insertion_point(field_unsafe_arena_release:bto.DumpRecordResponse.data)
  GOOGLE_DCHECK(GetArena() != nullptr);
  
  return data_.UnsafeArenaRelease(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      GetArena());
}
inline void DumpRecordResponse::unsafe_arena_set_allocated_data(
    std::string* data) {
  GOOGLE_DCHECK(GetArena() != nullptr);
  if (data != nullptr) {
    
  } else {
    
  }
  data_.UnsafeArenaSetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      data, GetArena());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:bto.DumpRecordResponse.data)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace bto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_bto_2fir_5fservice_2eproto
