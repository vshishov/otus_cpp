#include "common.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

class CIPv4
{
public:
  CIPv4();
  ~CIPv4();

  bool readFromStr(const std::string& a_strIp);
  bool filter(std::initializer_list<uint8_t> list) const;
  bool filter_any(uint8_t a_nByte) const;
  friend std::ostream& operator<<(std::ostream& a_Out, const CIPv4& a_Obj);
  friend bool operator>(const CIPv4& a, const CIPv4& b);

private:
  static constexpr int m_nNumBytes = 4;
  std::array<uint8_t, m_nNumBytes> m_vBytes;
};

template<class TIpAddr>
class CIpPool
{
public:
  CIpPool()
  { }
  
  ~CIpPool()
  { }

  void read(std::istream& in)
  {
    std::string strLine;
    while (std::getline(in, strLine)) {
      auto vListOfStrings = split(strLine, '\t');
      if (vListOfStrings.size() > 0) {
        CIPv4 ipv4;      
        if (ipv4.readFromStr(vListOfStrings[0])) {
          m_vIpAddrs.push_back(ipv4);
        }
      }
    }
  }

  void add(const CIPv4& a_IpAddr)
  {
    m_vIpAddrs.push_back(a_IpAddr);
  }

  void sort_reverse()
  {
    std::sort(
      m_vIpAddrs.begin(), 
      m_vIpAddrs.end(), 
      [](CIPv4& a, CIPv4& b)
      {
        return a > b ;
      }
    );
  }
  
  friend std::ostream& operator<<(std::ostream& a_Out, const CIpPool<TIpAddr>& a_Obj)
  {
    for ( auto it = a_Obj.m_vIpAddrs.cbegin(); it != a_Obj.m_vIpAddrs.cend(); ++it ) {
      if ( it != a_Obj.m_vIpAddrs.cbegin() ) {
        a_Out << std::endl;
      }
      a_Out << (*it);
    }
    return a_Out;
  }

  template<typename... T>
  CIpPool<TIpAddr> filter(T&&... args)
  {
   return fill(
     [&] (TIpAddr& ip) -> bool 
     {
       return ip.filter({ std::forward<uint8_t>(args)... });
      }
    );
  }

  CIpPool<TIpAddr> filter_any(uint8_t a_nByte) 
  {
    return fill(
      [=] (TIpAddr& ip) -> bool 
      {
        return ip.filter_any(a_nByte);
      }
    );
  }

private:
  template<typename Func>
  CIpPool<TIpAddr> fill(Func func)
  {
    CIpPool<TIpAddr> _pool;
    for (auto ipaddr : m_vIpAddrs) {      
      if (func(ipaddr))  {
        _pool.add(ipaddr);
      }
    }
    return _pool;
  }

private:
  std::vector<TIpAddr> m_vIpAddrs;
};