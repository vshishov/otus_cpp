#include <iostream>
#include <string>
#include <vector>
#include <array>

std::vector<std::string> split(const std::string &str, char d);

class CIPv4
{
public:
  CIPv4();
  ~CIPv4();

  bool readFromStr(std::string& a_strIp);
  bool filter(std::initializer_list<uint8_t> list) const;
  bool filter_any(uint8_t a_nByte) const;
  friend std::ostream& operator<<(std::ostream& a_Out, const CIPv4& a_Obj);
  friend bool operator>(const CIPv4& a, const CIPv4& b);

private:
  static constexpr int m_nNumBytes = 4;
  std::array<uint8_t, m_nNumBytes> m_vBytes;
};

class CIpPool
{
public:
  CIpPool();
  ~CIpPool();

  void read(std::istream& in);
  void add(const CIPv4& a_IpAddr);
  void sort_reverse();
  size_t size() const;
  
  friend std::ostream& operator<<(std::ostream& a_out, const CIpPool& a_Obj);

  template<typename... T>
  CIpPool filter(T&&... args)
  {
   return fill(
     [&] (CIPv4& ip) -> bool 
     {
       return ip.filter({ std::forward<uint8_t>(args)... });
      }
    );
  }

  CIpPool filter_any(uint8_t a_nByte) 
  {
    return fill(
      [=] (CIPv4& ip) -> bool 
      {
        return ip.filter_any(a_nByte);
      }
    );
  }

private:
  template<typename Func>
  CIpPool fill(Func func)
  {
    CIpPool _pool;
    for (auto ipaddr : m_vIpAddrs) {      
      if (func(ipaddr))  {
        _pool.add(ipaddr);
      }
    }
    return _pool;
  }

private:
  std::vector<CIPv4> m_vIpAddrs;
};