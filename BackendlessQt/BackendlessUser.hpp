//
//  BackendlessUser.hpp
//  BackendlessQt
//
//  Created by Roman Podymov on 07/08/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#ifndef BACKENDLESS_USER_H
#define BACKENDLESS_USER_H

#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QJsonParseError>
#include "BasicAPI.hpp"

class BackendlessRegisterUserRepresentable {
public:
    virtual ~BackendlessRegisterUserRepresentable() = default;
    virtual PostParams getAllParams() = 0;
};

struct BasicBackendlessRegisterUser: BackendlessRegisterUserRepresentable {
public:
    BasicBackendlessRegisterUser(
        QString _email,
        QString _password
    );

    PostParams getAllParams() override;

protected:
    QString email;
    QString password;
};

struct BackendlessSignInUser {
    QString userToken;

    BackendlessSignInUser(
        QJsonObject jsonObject
    ): userToken(jsonObject["user-token"].toString()) {

    }
};

#endif
