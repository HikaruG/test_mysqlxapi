#include "test.h"

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

  if(mysqlx::Scheme** clientScheme = newSession.getSchema(globalConfigContext->SqlDbname())){
    globalMysqlClient->ClientScheme_=&clientScheme;
  } else {
    throw ErrorAndLog("ClientDatabase could not be set");
  }
  if(mysqlx::Table clientTable = globalMysqlClient->SqlDbname()->getTable(globalConfigContext->SqlTable())){
    globalMysqlClient->ClientTable_= &clientTable;
  } else {
    throw ErrorAndLog("ClientTable could not be set");
  }
}

std::string* MysqlClient::CreateHostname(){
  std::char id = globalMysqlClient->ClientTable_.select("*").execute().count();
  print("this is the current id: %c",id);
  std::string hostname = "hostname";
  hostname += "_";
  hostname += id;
  try{
    auto globalMysqlClient->ClientTable_.insert("hostname").values(hostname).execute();
    return hostname;
  }
  catch(const Error &err){
    cout << "The folloing error occured: " << err << endl;
    return nullptr;
  }
}
