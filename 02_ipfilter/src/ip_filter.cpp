#include "common.h"

#include "ip_filter.h"

#include <cstdlib>
#include <algorithm>
#include <stdexcept>

CIPv4::CIPv4()
{ }

CIPv4::~CIPv4()
{ }

bool CIPv4::readFromStr(const std::string& a_strIp)
{
  auto listBytes = split(a_strIp, '.');
  if (listBytes.size() == m_nNumBytes ) {
    for ( int i = 0; i < m_nNumBytes; ++i) {   
      try {  
        int nByte = std::stoi(listBytes[i].c_str());
        if (nByte >= 0 && nByte <= 255) {
          m_vBytes[i] = nByte;          
        }
        else {
          throw std::out_of_range {"Out of range for IP address version 4"};
        }        
      }
      catch (std::exception& ex) {
        return false;
      }
    }
    return true;
  }

  return false;
}

bool CIPv4::filter(std::initializer_list<uint8_t> list) const
{
  std::vector<uint8_t> vBytes(list);
  if (vBytes.size() > 4) {
    std::cout << "error";
  }

  for (size_t i = 0; i < vBytes.size(); ++i) {
    if (m_vBytes[i] != vBytes[i]) {
      return false;
    }
  }
  return true; 
}

bool CIPv4::filter_any(uint8_t a_nByte) const
{
  for (auto byte : m_vBytes) {
    if (byte == a_nByte) {
      return true;
    }
  } 
  return false;
}

std::ostream& operator<<(std::ostream& a_Out, const CIPv4& a_Obj)
{
  for ( auto it = a_Obj.m_vBytes.cbegin(); it != a_Obj.m_vBytes.cend(); ++it ) {
    if ( it != a_Obj.m_vBytes.cbegin() ) {
      a_Out << '.';
    }
    a_Out << (int)*it;
  }
  return a_Out;
}

bool operator>(const CIPv4& a_ObjA, const CIPv4& a_ObjB)
{
  size_t szCount = std::min(a_ObjA.m_vBytes.size(), a_ObjA.m_vBytes.size());
  for (size_t i = 0; i < szCount; ++i) {
    if (a_ObjA.m_vBytes[i] != a_ObjB.m_vBytes[i]) {
      return (a_ObjA.m_vBytes[i] > a_ObjB.m_vBytes[i]);
    }
  }
  return false;
}

CIpPool::CIpPool() 
{ }

CIpPool::~CIpPool() 
{ }

void CIpPool::read(std::istream& in)
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

void CIpPool::add(const CIPv4& a_IpAddr)
{
  m_vIpAddrs.push_back(a_IpAddr);
}

void CIpPool::sort_reverse()
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

std::ostream& operator<<(std::ostream& a_Out, const CIpPool& a_Obj)
{
  for ( auto it = a_Obj.m_vIpAddrs.cbegin(); it != a_Obj.m_vIpAddrs.cend(); ++it ) {
    if ( it != a_Obj.m_vIpAddrs.cbegin() ) {
      a_Out << std::endl;
    }
    a_Out << (*it);
  }
  return a_Out;
}