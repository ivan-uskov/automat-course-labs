<!DOCTYPE html>
<html lang="ru">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Game of Live</title>
    <link rel="stylesheet" href="/css/main.css" />
    <link rel="stylesheet" href="/css/life.css" />
    <script type="text/javascript" src="/js/lib/jquery.js"></script>
    <script type="text/javascript" src="/js/classes/life/Cell.class.js"></script>
    <script type="text/javascript" src="/js/classes/life/Point.class.js"></script>
    <script type="text/javascript" src="/js/classes/life/World.class.js"></script>
    <script type="text/javascript" src="/js/live.js"></script>
  </head>
  <body>
    <canvas id="viewport"></canvas>
    <div class="controls">
      <button id="startButton" class="control">Start</button>
      <button id="stopButton" class="control hidden">Stop</button>
      <button id="clearButton" class="control">Clear</button><br />
      <button id="fillRandomButton" class="control">FillRandom</button>
      <div class="insert_controls control" id="insertControls">
        <p>Select insert mode and click on grid to add</p>
        <p>
          <input type="radio" name="insert_mode" id="glider" value="glider" checked>
          <label for="glider">Glider</label>
        </p>
        <p>
          <input type="radio" name="insert_mode" id="gosperGun" value="gosperGun">
          <label for="gosperGun">Gosper gun</label>
        </p>
        <p>
          <input type="radio" name="insert_mode" id="block" value="block" checked>
          <label for="block">Block</label>
        </p>
        <p>
          <input type="radio" name="insert_mode" id="pulsar" value="pulsar" checked>
          <label for="pulsar">Pulsar</label>
        </p>
        <p>
          <input type="radio" name="insert_mode" id="boat" value="boat" checked>
          <label for="boat">Boat</label>
        </p>
        <p>
          <input type="radio" name="insert_mode" id="lwss" value="lwss" checked>
          <label for="lwss">LWSS</label>
        </p>
        <p>
          <input type="radio" name="insert_mode" id="beacon" value="beacon" checked>
          <label for="beacon">Beacon</label>
        </p>
        <p>
          <input type="radio" name="insert_mode" id="point" value="point">
          <label for="point">Point</label>
        </p>
      </div>
    </div>
  </body>
</html>