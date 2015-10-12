function initializeFormObject()
{
	var formElements = {
		userNickname: isNicknameValid,
		userEmail:    isEmailValid,
		userPassword: isPasswordValid
	};

	var formDuplicateElements = {
		userPasswordRepeat: 'userPassword'
	};

	return new Form('registerUserForm', formElements, formDuplicateElements);
}

function initializeForm()
{
	var form = initializeFormObject();
	form.listenSubmit();
}

$(function(){
	initializeForm();
});
