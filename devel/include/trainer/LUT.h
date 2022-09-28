// Generated by gencpp from file trainer/LUT.msg
// DO NOT EDIT!


#ifndef TRAINER_MESSAGE_LUT_H
#define TRAINER_MESSAGE_LUT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace trainer
{
template <class ContainerAllocator>
struct LUT_
{
  typedef LUT_<ContainerAllocator> Type;

  LUT_()
    : data()  {
    }
  LUT_(const ContainerAllocator& _alloc)
    : data(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<uint16_t, typename ContainerAllocator::template rebind<uint16_t>::other >  _data_type;
  _data_type data;





  typedef boost::shared_ptr< ::trainer::LUT_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::trainer::LUT_<ContainerAllocator> const> ConstPtr;

}; // struct LUT_

typedef ::trainer::LUT_<std::allocator<void> > LUT;

typedef boost::shared_ptr< ::trainer::LUT > LUTPtr;
typedef boost::shared_ptr< ::trainer::LUT const> LUTConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::trainer::LUT_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::trainer::LUT_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::trainer::LUT_<ContainerAllocator1> & lhs, const ::trainer::LUT_<ContainerAllocator2> & rhs)
{
  return lhs.data == rhs.data;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::trainer::LUT_<ContainerAllocator1> & lhs, const ::trainer::LUT_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace trainer

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::trainer::LUT_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::trainer::LUT_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trainer::LUT_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::trainer::LUT_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trainer::LUT_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::trainer::LUT_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::trainer::LUT_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e066daa5966378a57445687eb65bfa3b";
  }

  static const char* value(const ::trainer::LUT_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe066daa5966378a5ULL;
  static const uint64_t static_value2 = 0x7445687eb65bfa3bULL;
};

template<class ContainerAllocator>
struct DataType< ::trainer::LUT_<ContainerAllocator> >
{
  static const char* value()
  {
    return "trainer/LUT";
  }

  static const char* value(const ::trainer::LUT_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::trainer::LUT_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint16[] data\n"
;
  }

  static const char* value(const ::trainer::LUT_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::trainer::LUT_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LUT_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::trainer::LUT_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::trainer::LUT_<ContainerAllocator>& v)
  {
    s << indent << "data[]" << std::endl;
    for (size_t i = 0; i < v.data.size(); ++i)
    {
      s << indent << "  data[" << i << "]: ";
      Printer<uint16_t>::stream(s, indent + "  ", v.data[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // TRAINER_MESSAGE_LUT_H
