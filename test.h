#include <mysqlx/xdevapi.h>

class MysqlClient {
public:
  static void Initialize();
  static MysqlClient* Get();
  std::string* CreateHostname();
  std::string* GetHostname(std::string& hostname);
  std::string* GetToken(std::string& hostname);
  bool PutData(std::string& hostname, std::string& token);
private:
  MysqlClient() = default;
  static MysqlClient* globalMysqlClient; //cant put the ** ?
  static mysqlx::Session* ClientSession_;//cant put the ** ?
  static mysqlx::Schema* ClientSchema_;//cant put the ** ?
  static mysqlx::Table& ClientTable_;
};
