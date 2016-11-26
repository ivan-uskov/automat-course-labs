var World = function(x0, y0)
{
    this.age = 0;
    this.map = [];

    this.started = false;

    this._borderMap = [];
    this._changeQueue = [];
    this._timeout = null;
    this.size = new Point();
    this.speed = 100;
    var x = 10;
    var y = 10;

    if (x0 !== undefined)
    {
        x = x0;
    }

    if (y0  !== undefined)
    {
        y = y0;
    }

    this.drawCellCallback = function(x, y, color)
    {
    };

    this.eraseCellCallback = function(x, y)
    {
    };

    this.init = function(x, y)
    {
        this.age = 0;

        this.size.x = x;
        this.size.y = y;

        this.map = [];
        for (var i = 0; i <= this.size.x; i++)
        {
            this.map[i] = [];
        }

        x = y = 0;

        for (i = 0; i < (this.size.x * this.size.y) / 2; i++)
        {

            x = Math.round(Math.random() * this.size.x);
            if (!this.map[x])
            {
                this.map[x] = [];
            }

            y = Math.round(Math.random() * this.size.y);
            this.map[x][y] = new Cell();

            this.drawCellCallback(x, y);
        }

        this._changeQueue =
        [
            [undefined, undefined],
            [undefined, undefined]
        ];

    };

    this.start = function()
    {
        this.started = true;
        this.step();
    };

    this.stop = function()
    {
        clearTimeout(this._timeout);
        this.started = false;
    };

    this.step = function()
    {
        this.age++;

        this._borderMap = [];

        var burnNote = [],
            deathNote = [];

        var cnt = 0;
        var color;

        for (i in this.map)
        {
            for (j in this.map[i])
            {

                cnt = this.checkNeighbors(i, j, true);

                if (cnt < 2 || cnt > 3)
                {
                    deathNote.push([i, j]);
                }

                this.drawCellCallback(i, j, this.map[i][j].getColor());

                this.map[i][j].grow();
            }
        }

        for (i in this._borderMap)
        {
            for (var j in this._borderMap[i])
            {

                cnt = this.checkNeighbors(i, j, false);

                if (cnt === 3)
                {
                    burnNote.push([i, j]);
                }
            }
        }

        for (i in burnNote)
        {
            this.burnCell(burnNote[i][0], burnNote[i][1]);
        }


        for (var i in deathNote)
        {
            this.killCell(
                deathNote[i][0],
                deathNote[i][1]
            );
        }

        if (!deathNote.length)
        {
            this.stop();
        }

        this._changeQueue.push([burnNote.length, deathNote.length]);
        if (this._changeQueue.length > 3)
        {
            this._changeQueue.shift();
        }

        if (this._changeQueue[2][0] === deathNote.length &&
            this._changeQueue[2][1] === burnNote.length &&
            this._changeQueue[1][0] === deathNote.length &&
            this._changeQueue[1][1] === burnNote.length &&
            this._changeQueue[0][0] === deathNote.length &&
            this._changeQueue[0][1] === burnNote.length
        )
        {
            this.stop();
        }

        if (this.started)
        {
            var that = this;
            this._timeout = setTimeout(
                function()
                {
                    if (that.started)
                    {
                        that.step();
                    }
                },
                this.speed
            );
        }
    };

    this.checkNeighbors = function(x, y, toCheckList)
    {

        var count = 0,
            ox = 0,
            oy = 0;

        x = parseInt(x);
        y = parseInt(y);

        var width = this.size.x + 1;
        var height = this.size.y + 1;

        for (var i = x - 1; i <= x + 1; i++)
        {
            ox = (i + width) % width;

            for (var j = y - 1; j <= y + 1; j++)
            {
                if (i === x && j === y)
                {
                    continue;
                }

                oy = (j + height) % height;

                if (this.map[ox] && this.map[ox][oy] !== undefined)
                {
                    count++;
                }
                else if (toCheckList)
                {
                    if (!this._borderMap[ox])
                    {
                        this._borderMap[ox] = [];
                    }
                    this._borderMap[ox][oy] = true;
                }
            }
        }

        return count;
    };

    this.burnCell = function(x, y)
    {
        if (!this.map[x])
        {
            this.map[x] = [];
        }
        this.map[x][y] = new Cell;

        this.drawCellCallback(x, y, 'hsl(350, 100%, 50%)');
    };

    this.killCell = function(x, y)
    {
        delete this.map[x][y];

        this.eraseCellCallback(x, y);
    };

    this._burnObject = function(object, x, y)
    {
        for (var dy = 0; dy < object.length; ++dy)
        {
            for (var dx = 0; dx < object[0].length; ++dx)
            {
                if (object[dy][dx])
                {
                    this.burnCell(x + dx, y + dy);
                }
            }
        }
    };

    this.burnGlider = function(x, y)
    {
        var glider = [
            [0, 1, 0],
            [0, 0, 1],
            [1, 1, 1]
        ];

        this._burnObject(glider, x, y);
    };

    this.burnBlock = function(x, y)
    {
        var block = [
            [1, 1],
            [1, 1]
        ];

        this._burnObject(block, x, y);
    };

    this.burnBoat = function(x, y)
    {
        var boat = [
            [1, 1, 0],
            [1, 0, 1],
            [0, 1, 0]
        ];

        this._burnObject(boat, x, y);
    };

    this.burnBeacon = function(x, y)
    {
        var beacon = [
            [1, 1, 0, 0],
            [1, 0, 0, 0],
            [0, 0, 0, 1],
            [0, 0, 1, 1]
        ];

        this._burnObject(beacon, x, y);
    };

    this.burnLWSS = function(x, y)
    {
        var boat = [
            [1, 0, 0, 1, 0],
            [0, 0, 0, 0, 1],
            [1, 0, 0, 0, 1],
            [0, 1, 1, 1, 1]
        ];

        this._burnObject(boat, x, y);
    };

    this.burnPulsar = function(x, y)
    {
        var pulsar = [
            [0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1],
            [0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0],
            [1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0]
        ];

        this._burnObject(pulsar, x, y);
    };

    this.burnGosperGun = function(x, y)
    {
        var gosperGun = [
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1],
            [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        ];

        this._burnObject(gosperGun, x, y);
    };

    this.clear = function()
    {
        for (var i in this.map)
        {
            for (var j in this.map[i])
            {
                this.killCell(i, j);
            }
        }
    };

    this.init(x, y);
};