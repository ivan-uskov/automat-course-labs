var FormField = function(id, validator)
{
	var field = $('#' + id);
	var container = field.parents('.form-group');
	var errorHolder = container.find('.alert');
	var validator = validator;

	this.validate = function()
	{
		var isValid = validator(this.getValue());
		if (isValid)
		{
			hideError();
		}
		else
		{
			showError();
		}

		return isValid;
	};

	this.getValue = function()
	{
		return field.val();
	};

	this.handleBlur = function()
	{
		var thisPtr = this;
		field.blur(function() {
			thisPtr.validate();
		});
	};

	function showError()
	{
		errorHolder.removeClass('hidden');
	}

	function hideError()
	{
		errorHolder.addClass('hidden');
	}
};
