package main

import "github.com/gin-gonic/gin"
import "net/http"

func RenderUserPage(ctx *gin.Context, user *SiteUser) {
	ctx.HTML(http.StatusOK, "reg-results.tpl", gin.H{
		"title":        "Automata Theory - Lab 1, form validation",
		"userNickname": user.nickname,
		"userEmail":    user.email,
	})
}

func GetRenderFormPage(ctx *gin.Context) {
	renderRegisterForm(ctx, nil)
}

func PostRenderFormPage(ctx *gin.Context, cache *SiteUsersCache) {
	user := &SiteUser{
		nickname:       ctx.PostForm("nickname"),
		email:          ctx.PostForm("email"),
		password:       ctx.PostForm("password"),
		passwordRepeat: ctx.PostForm("password_repeat"),
	}

	validator := NewRegisterFormValidator()
	checkResult := validator.Check(user)

	if checkResult.status == UserValid {
		cache.AddUser(user)
		RenderUserPage(ctx, user)
	} else {
		renderRegisterForm(ctx, &checkResult)
	}
}

func fillRegisterResultTplData(tplData map[string]interface{}, result *RegisterResult) {
	tplData["nickname"] = result.user.nickname
	tplData["email"] = result.user.email

	switch result.status {
	case UserInvalidNickname:
		tplData["hideAlertName"] = false
	case UserInvalidEmail:
		tplData["hideAlertEmail"] = false
	case UserWeakPassword:
		tplData["hideAlertPassword"] = false
	case UserPasswordMismatch:
		tplData["hideAlertRepeatPassword"] = false
	}
}

func renderRegisterForm(ctx *gin.Context, result *RegisterResult) {
	tplData := gin.H{
		"title":                   "Automata Theory - Lab 1, form validation",
		"hideAlertName":           true,
		"hideAlertEmail":          true,
		"hideAlertPassword":       true,
		"hideAlertRepeatPassword": true,
		"nickname":                "",
		"email":                   "",
	}
	if result != nil {
		fillRegisterResultTplData(tplData, result)
	}
	ctx.HTML(http.StatusOK, "reg-form.tpl", tplData)
}
