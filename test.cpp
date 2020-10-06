#include "test.h"
#include<iostream>
#include "exception.h"

void MysqlClient::Initialize(){
  if (globalMysqlClient != nullptr) {
    throw ErrorAndLog(
        "Called MysqlClient::Initialize after MysqlClient was initialized");
  }
  globalMysqlClient = new MysqlClient;
  mysqlx::Session newSession(
    "tokenauth.cg2rbsdaibs8.ap-northeast-1.rds.amazonaws.com",
    "3306",
    "neukind",
    "Neukind.jp");

  if(mysqlx::Schema clientScheme = newSession.getSchema("tokens")){
    globalMysqlClient->ClientSchema_=*clientScheme;
  } else {
    throw ErrorAndLog("ClientDatabase could not be set");
  }
  if(mysqlx::Table clientTable = globalMysqlClient->ClientSchema_->getTable("hostname",check_exists=true)){
    globalMysqlClient->ClientTable_= &clientTable;
  } else {
    throw ErrorAndLog("ClientTable could not be set");
  }
}

MysqlClient* MysqlClient::Get(){
  if(globalMysqlClient == nullptr){
    throw ErrorAndLog("Get called before MysqlClient::Initialize");
  }
  return globalMysqlClient;
}

std::string* MysqlClient::CreateHostname(){
  char id = globalMysqlClient->ClientTable_.select("*").execute().count();
  printf("this is the current id: %c",id);
  std::string hostname = "hostname";
  hostname += "_";
  hostname += id;
    if(!globalMysqlClient->ClientTable_.insert("hostname").values(hostname).execute()){
      throw ErrorAndLog("Hostname could not be inserted in the DB")
    }
    return *hostname;
}

int main(){
  MysqlClient::Initialize();
  MysqlClient::Get()->CreateHostname();
  return 0;
}
