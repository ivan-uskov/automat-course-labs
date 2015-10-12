package main

import "github.com/gin-gonic/gin"

func setupStatic(router *gin.Engine) {
	router.Static("/css", STATIC_DIR+"css")
	router.Static("/js", STATIC_DIR+"js")
	router.LoadHTMLGlob(STATIC_DIR + "tpl/*.tpl")
}

func setupPages(router *gin.Engine, cache *SiteUsersCache) {
	router.GET("/form", GetRenderFormPage)
	router.POST("/form_ajax", func(ctx *gin.Context) {
		PostRenderFormPage(ctx, cache)
	})
}

func main() {
	cache := NewSiteUsersCache()

	router := gin.Default()
	setupStatic(router)
	setupPages(router, cache)

	router.Run(":8080")
}
