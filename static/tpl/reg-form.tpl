<!DOCTYPE html>
<html lang="ru">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="stylesheet" href="/css/bootstrap.min.css" />
    <link rel="stylesheet" href="/css/bootstrap-theme.min.css" />
    <link rel="stylesheet" href="/css/main.css" />
    <script type="text/javascript" src="/js/lib/jquery.js"></script>
    <script type="text/javascript" src="/js/form_validator.js"></script>
    <script type="text/javascript" src="/js/classes/FormField.class.js"></script>
    <script type="text/javascript" src="/js/classes/DuplicateFormField.class.js"></script>
    <script type="text/javascript" src="/js/classes/Form.class.js"></script>
    <script type="text/javascript" src="/js/form_handler.js"></script>
  </head>
  <body>
    <div class="container">
      <div class="row">
        <h2>{{.title}}</h2>
      </div>
      <div class="row">
        <form action="/form_ajax" method="POST" id="registerUserForm">
          <div class="form-group">
            <label for="userNickname">Nickname</label>
            <div class="alert alert-danger{{if .hideAlertName}} hidden{{end}}" role="alert">Invalid nickname!</div>
            <input type="text" class="form-control" id="userNickname" placeholder="Your Nickname" name="nickname" value="{{.nickname}}">
            <p class="help-block">Nickname should contain only English letters, digits and underscores.</p>
          </div>
          <div class="form-group">
            <label for="userEmail">Email address</label>
            <div class="alert alert-danger{{if .hideAlertEmail}} hidden{{end}}" role="alert">Invalid email</div>
            <input type="text" class="form-control" id="userEmail" placeholder="Your Email" name="email" value="{{.email}}">
            <p class="help-block">Only GMail, Yandex Mail and Mail.ru email addresses allowed.</p>
          </div>
          <div class="form-group">
            <label for="userPassword">Password</label>
            <div class="alert alert-danger{{if .hideAlertPassword}} hidden{{end}}" role="alert">Invalid password</div>
            <input type="password" class="form-control" id="userPassword" placeholder="Your New Password" name="password">
          </div>
          <div class="form-group">
            <div class="alert alert-danger{{if .hideAlertRepeatPassword}} hidden{{end}}" role="alert">Password should be equals!</div>
            <input type="password" class="form-control" id="userPasswordRepeat" placeholder="Repeat Password" name="password_repeat">
            <p class="help-block">Password should have at least 6 characters with letters and digits</p>
          </div>
          <button type="submit" class="btn btn-default">Submit</button>
        </form>
      </div>
    </div>
  </body>
</html>
