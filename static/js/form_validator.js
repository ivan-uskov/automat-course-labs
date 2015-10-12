var MIN_PASSWORD_LENGTH = 6;

function isEmailValid(email)
{
    return /^([0-9a-z]+([\.\-\_][0-9a-z]+)*)@(gmail\.com|yandex\.ru|mail\.ru)$/.test(email.toLowerCase());
}

function isPasswordValid(password)
{
    var lowerPass               = password.toLowerCase();
    var isPasswordLengthCorrect = (lowerPass.length >= MIN_PASSWORD_LENGTH);
    var passwordHasLetter       = /[a-z]/.test(lowerPass);
    var passwordHasDigit        = /[0-9]/.test(lowerPass);

    return isPasswordLengthCorrect &&
           passwordHasLetter       &&
           passwordHasDigit;
}

function isNicknameValid(nickname)
{
    return /^[a-zA-Z0-9\_]+$/.test(nickname);
}
