package main

import "regexp"
import "strings"

const (
    UserValid = iota
    UserInvalidNickname
    UserInvalidEmail
    UserWeakPassword
    UserPasswordMismatch
)

const MIN_PASSWORD_LENGTH = 6

type RegisterResult struct {
    status int32
    user   *SiteUser
}

type RegisterFormValidator struct {
}

func NewRegisterFormValidator() *RegisterFormValidator {
    return new(RegisterFormValidator)
}

func (self *RegisterFormValidator) Check(user *SiteUser) RegisterResult {
    result := RegisterResult{
        status: UserValid,
        user:   user,
    }
    if !isNicknameValid(user.nickname) {
        result.status = UserInvalidNickname
    } else if !isEmailValid(user.email) {
        result.status = UserInvalidEmail
    } else if !isPasswordValid(user.password) {
        result.status = UserWeakPassword
    } else if user.password != user.passwordRepeat {
        result.status = UserPasswordMismatch
    }
    return result
}

func isNicknameValid(nickname string) bool {
    return regexp.MustCompile(`^[a-zA-Z0-9\_]+$`).MatchString(nickname)
}

func isEmailValid(email string) bool {
    lowerEmail := strings.ToLower(email)
    return regexp.MustCompile(`^([0-9a-z]+([\.\-\_][0-9a-z]+)*)@(gmail\.com|yandex\.ru|mail\.ru)$`).MatchString(lowerEmail)
}

func isPasswordValid(password string) bool {
    isPasswordLengthCorrect := len(password) >= MIN_PASSWORD_LENGTH
    passwordHasLetter := regexp.MustCompile(`[a-zA-Z]`).MatchString(password)
    passwordHasDigit := regexp.MustCompile(`[0-9]`).MatchString(password)

    return isPasswordLengthCorrect && passwordHasLetter && passwordHasDigit
}
