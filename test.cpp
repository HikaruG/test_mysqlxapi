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
  if(newSession.getSchema("tokens").existsInDatabase()){
    globalMysqlClient->ClientSchema_= &newSession.getSchema("tokens");
  } else {
    throw ErrorAndLog("ClientDatabase could not be set");
  }
  try{// Table Schema::getTable(name,check_exists) throw_error("Table does not exist") or return Table
    mysqlx::Table result = globalMysqlClient->ClientSchema_->getTable("hostname",true);
    globalMysqlClient->ClientTable_= &result;
  }
  catch(const std::exception&){
    throw ErrorAndLog("ClientTable could not be set");
  }
}

MysqlClient* MysqlClient::Get(){
  if(globalMysqlClient == nullptr){
    throw ErrorAndLog("Get called before MysqlClient::Initialize");
  }
  return globalMysqlClient;
}

void MysqlClient::CreateHostname(std::string* hostname){
  char id = globalMysqlClient->ClientTable_->select("*").execute().count();
  printf("this is the current id: %c",id);
  std::string newname = "hostname";
  newname += "_";
  newname += id;
    //need to check the return value of a failed execute
    if(globalMysqlClient->ClientTable_->insert("hostname").values(hostname).execute() == nullptr){
      throw ErrorAndLog("Hostname could not be inserted in the DB");
    }
    *hostname=newname;
}

int main(){
  MysqlClient::Initialize();
  MysqlClient::Get()->CreateHostname();
  return 0;
}
