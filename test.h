#include <mysqlx/xdevapi.h>

class MysqlClient {
public:
  static void Initialize();
  static MysqlClient* Get();
  std::string CreateHostname();
  std::string GetHostname(std::string& hostname);
  std::string GetToken(std::string& hostname){
  bool PutData(std::string& hostname, std::string& token);
private:
  MysqlClient() = default;
  static MysqlClient** globalMysqlClient;
  static mysqlx::Session** ClientSession_;
  static mysqlx::Scheme** ClientScheme_;
  static mysqlx::Table& ClientTable_;
}
