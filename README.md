# BackendlessQt

Qt wrapper for [Backendless](https://backendless.com).

## How to use it?

Create a new API instance
```
BackendlessAPI api(API("YOUR_APP_ID", "YOUR_REST_API_KEY"));
```

Register a new user
```
QObject::connect(&api.userAPI, &BackendlessUserAPI::registerUserResult, this, [](){
    // User is registered
});
api.userAPI.registerUser(BackendlessRegisterUser("myemail@email.com", "Roman", "Password"));
```

Sign in
```
QObject::connect(&api.userAPI, &BackendlessUserAPI::signInUserSuccess, this, [](auto user){
    // User is signed in
});
QObject::connect(&api.userAPI, &BackendlessUserAPI::signInUserErrorBackendless, this, [](auto error){
    // Wrong credentials
});
api.userAPI.signInUser("myemail@email.com", "Password");
```

Validate user token
```
QObject::connect(&api.userAPI, &BackendlessUserAPI::validateUserTokenSuccess, this, [](auto isValid){
    // Is user token valid?
});
api.userAPI.validateUserToken();
```

Add a new item to a table
```
QObject::connect(&api, &BackendlessAPI::itemAdded, this, [&](){
    // Item is added
});
api.addItemToTable(
    "TableName", 
    {
        {"propery", "value"}, 
        {"anotherProperty", "value"}
    }
);
```

Read table items
```
QObject::connect(&api, &BackendlessAPI::tableItemsLoaded, this, [&](auto response){
    qDebug() << "Loaded " << response;
});
api.loadTableItems("TableName");
```
