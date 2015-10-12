var DuplicateFormField = function(id, dependedField)
{
	var field = $('#' + id);
	var container = field.parents('.form-group');
	var errorHolder = container.find('.alert');
	var dependedField = dependedField;

	this.validate = function()
	{
		var isValid = this.getValue() == dependedField.getValue();
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
