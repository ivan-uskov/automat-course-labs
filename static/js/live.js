$(function()
{
    function calcOffset()
    {
        var hor = canvas.width % cellSize;
        var vert = canvas.height % cellSize;

        topLeft.x = Math.round(hor / 2);
        topLeft.y = Math.round(vert / 2);

        bottomRight.x = Math.round(canvas.width - hor / 2);
        bottomRight.y = Math.round(canvas.height - vert / 2);

        size.x = Math.floor(canvas.width / cellSize) - 1;
        size.y = Math.floor(canvas.height / cellSize) - 1;
    }

    function drawBackground()
    {
        context.fillStyle = lineColor;
        context.fillRect(0, 0, canvas.width, canvas.height);
        context.fillStyle = bgColor;
        context.fillRect(
            topLeft.x,
            topLeft.y,
            bottomRight.x - topLeft.x,
            bottomRight.y - topLeft.y
        );
    }

    function drawGreed()
    {
        context.strokeStyle = lineColor;
        context.lineWidth = 1;

        context.beginPath();

        for (var i = topLeft.x; i <= bottomRight.x; i += cellSize) {
            context.moveTo(i, topLeft.y);
            context.lineTo(i, bottomRight.y);
        }

        for (var i = topLeft.y; i <= bottomRight.y; i += cellSize) {
            context.moveTo(topLeft.x, i);
            context.lineTo(bottomRight.x, i);
        }

        context.stroke();
    }

    function fillCell(x, y, color)
    {
        context.fillStyle = color;
        context.fillRect(
            topLeft.x + x * cellSize + 1,
            topLeft.y + y * cellSize + 1,
            cellSize - 2,
            cellSize - 2
        );
    }

    function canvasClick(evt)
    {
        var canvasOffset = $(this).offset();

        var x = Math.floor((evt.x - canvasOffset.left) / cellSize);
        var y = Math.floor((evt.y - canvasOffset.top) / cellSize);

        var currentInsertMode = $('input[name=insert_mode]:checked').val();
        switch (currentInsertMode)
        {
            case 'glider':
                return world.burnGlider(x, y);
            case 'gosperGun':
                return world.burnGosperGun(x, y);
            case 'block':
                return world.burnBlock(x, y);
            case 'pulsar':
                return world.burnPulsar(x, y);
            case 'boat':
                return world.burnBoat(x, y);
            case 'lwss':
                return world.burnLWSS(x, y);
            case 'beacon':
                return world.burnBeacon(x, y);
            case 'point':
                return world.burnCell(x, y);
        }
    }

    function keyPress(evt)
    {
        switch (evt.keyCode) {
            case 13: // Enter
                if (world.started)
                    world.stop();
                else
                    world.start();
                break;

            case 32: // Space
                if (!world.started)
                    world.step();
                break;

            case 91: // ]
                world.speed += 50;
                break;

            case 93: // [
                var speed = world.speed - 50;
                if (speed < 50)
                    speed = 50;
                world.speed = speed;
                break;

            case 114: // r
                world.stop();
                drawBackground();
                drawGreed();
                world.init(world.size.x, world.size.y);
                world.start();
                break;

            case 99: // c
                world.clear();
                break;
        }
    }

    var bgColor = '#EEE';
    var lineColor = '#BBB';
    var cellSize = 5;

    var canvas = document.getElementById('viewport');
    canvas.height = 0.8 * document.body.clientHeight;
    canvas.width = 0.8 * document.body.clientWidth;

    var context = canvas.getContext('2d');
    var topLeft = new Point();
    var bottomRight = new Point();
    var size = new Point();

    calcOffset();
    drawBackground();
    drawGreed();

    var world = new World(size.x, size.y);

    world.drawCellCallback = function(x, y, color)
    {
        fillCell(x, y, color);
    };
    world.eraseCellCallback = function(x, y)
    {
        fillCell(x, y, bgColor);
    };

    world.speed = 50;
    world.step();
    world.clear();
    canvas.onclick = canvasClick;
    document.body.onkeypress = keyPress;

    var fillRandomButton = $('#fillRandomButton');
    var startButton = $('#startButton');
    var stopButton = $('#stopButton');

    startButton.click(function(){
        world.start();
        fillRandomButton.hide();
        startButton.hide();
        stopButton.show();
    });

    stopButton.click(function(){
        world.stop();
        fillRandomButton.show();
        stopButton.hide();
        startButton.show();
    });

    fillRandomButton.click(function(){
        world.clear();
        world.init(world.size.x, world.size.y);
        world.step();
    });

    $('#clearButton').click(function(){
        world.clear();
    });
});