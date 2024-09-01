//
//  BackendlessUser.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BACKENDLESS_USER_H
#define BACKENDLESS_USER_H

#include <QString>

struct BackendlessRegisterUser {
    QString email;
    QString name;
    QString password;

    BackendlessRegisterUser(
        QString _email,
        QString _name,
        QString _password
    ): email(_email), name(_name), password(_password) { }
};

struct BackendlessSignInUser {
    QString userToken;

    BackendlessSignInUser(
        QString _userToken
    ): userToken(_userToken) { }
};

#endif
