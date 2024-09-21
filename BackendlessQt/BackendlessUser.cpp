//
//  BackendlessUser.cpp
//  BackendlessQt
//
//  Created by Roman Podymov on 16/09/2024.
//  Copyright © 2024 BackendlessQt. All rights reserved.
//

#include "BackendlessUser.hpp"

BasicBackendlessRegisterUser::BasicBackendlessRegisterUser(
    QString _email,
    QString _password
): email(_email), password(_password) {
}

QMap<QString, QString> BasicBackendlessRegisterUser::getAllParams() {
    return {
        {"email", email},
        {"password", password}
    };
}
