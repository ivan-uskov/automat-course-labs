<!DOCTYPE html>
<html lang="ru">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="stylesheet" href="/css/bootstrap.min.css" />
    <link rel="stylesheet" href="/css/bootstrap-theme.min.css" />
    <link rel="stylesheet" href="/css/main.css" />
    <script type="text/javascript" src="/js/lib/jquery.js"></script>
    <script type="text/javascript" src="/js/classes/FormField.class.js"></script>
    <script type="text/javascript" src="/js/classes/Form.class.js"></script>
    <script type="text/javascript" src="/js/calculator.js"></script>
    <title>Calculator</title>
  </head>
  <body>
    <div class="container">
      <div class="row">
        <h2>Calculator</h2>
      </div>
      <div class="row">
        <form action="/calc_ajax" method="POST" id="calcForm">
          <div class="form-group">
            <label for="userNickname">Nickname</label>
            <div class="alert alert-danger hidden" role="alert">Invalid expression!</div>
            <input type="text" class="form-control" id="userExpression" placeholder="Your expression" name="nickname">
            <p class="help-block">Write your expression by numbers + - * /</p>
          </div>
          <button type="submit" class="btn btn-default">Submit</button>
        </form>
      </div>
    </div>
  </body>
</html>
