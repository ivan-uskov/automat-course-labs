var Cell = function()
{
    this.age = 0;

    this.grow = function()
    {
        this.age++;
    };

    this.getColor = function()
    {
        var color = this.age * 5;
        if (color > 250)
        {
            color = 250;
        }

        return 'hsl(' + color + ', 100%, 50%)';
    };
};