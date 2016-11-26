$(function()
{
    $('#calcForm').submit(function(){

        var form = $(this);
        var alert = form.find('.alert');
        var expression = form.find('#userExpression');
        expression.focus(function(){
            alert.addClass('hidden');
        });

        $.ajax({
            type: "POST",
            url: form.attr('action'),
            data: {expression: expression.val()},
            success: function(response) {
                if (response.success)
                {
                    expression.val(response.result);
                }
                else
                {
                    alert.html(response.message);
                    alert.removeClass('hidden');
                }
            }
        });
        return false;
    });
});
