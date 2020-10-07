#include "test.h"
#include<iostream>
#include "exception.h"

void MysqlClient::Initialize(mysqlx::Session* newSession){
  if (globalMysqlClient != nullptr) {
    throw ErrorAndLog(
        "Called MysqlClient::Initialize after MysqlClient was initialized");
  }
  globalMysqlClient = new MysqlClient;
  if (newSession == nullptr){
    throw ErrorAndLog(
        "Mysql session unavaible");
  }
  ClientSession_ = &newSession;
}

MysqlClient* MysqlClient::Get(){
  if(globalMysqlClient == nullptr){
    throw ErrorAndLog("Get called before MysqlClient::Initialize");
  }
  return globalMysqlClient;
}

void MysqlClient::CreateHostname(std::string* hostname){
  int id = int(globalMysqlClient->newSession->getSchema("tokens").getTable("hostname").select("*").execute().count());
  printf("this is the current id: %c",id);
  std::string newname = "hostname";
  id ++;
  newname += "_";
  newname += char(id);
    //need to check the return value of a failed execute
  try{
      globalMysqlClient->newSession->getSchema("tokens").getTable("hostname").insert("hostname").values(hostname).execute();
      *hostname=newname;
  }
  catch(const std::exception&){
    throw ErrorAndLog("Hostname could not be inserted in the DB");
  }
}

int main(){
  mysqlx::Session newSession(
    "tokenauth.cg2rbsdaibs8.ap-northeast-1.rds.amazonaws.com",
    "3306",
    "neukind",
    "Neukind.jp")
  std::string hostname;
  MysqlClient::Initialize(&newSession);
  MysqlClient::Get()->CreateHostname(&hostname);
  return 0;
}
