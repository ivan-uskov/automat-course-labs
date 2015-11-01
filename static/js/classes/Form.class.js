var Form = function(id, elementsMap, duplicateElementsMap)
{
    var jObject = $('#' + id);
    var formElements = {};
    var duplicateElements = {};
    initElements(elementsMap);
    initDuplicateElements(duplicateElementsMap);

    this.listenSubmit = function()
    {
        jObject.submit(function()
        {
            if (!validate())
            {
                return false;
            }
        });
    };

    function validate()
    {
        var isValid = true;
        $.each(formElements, function(key, formField)
        {
            isValid = isValid && formField.validate();
        });

        return isValid;
    }

    function initElements(elementsMap)
    {
        $.each(elementsMap, function(fieldId, validator)
        {
            var field = new FormField(fieldId, validator);
            field.handleBlur();

            formElements[fieldId] = field;
        });
    }

    function initDuplicateElements(duplicateElementsMap)
    {
        $.each(duplicateElementsMap, function(duplicateFieldId, dependedFieldId)
        {
            var dependedField = formElements.hasOwnProperty(dependedFieldId) ? formElements[dependedFieldId] : null;
            if (!dependedField)
            {
                throw new Error('Invalid form configuration!');
            }

            var field = new DuplicateFormField(duplicateFieldId, dependedField);
            field.handleBlur();

            duplicateElements[duplicateFieldId] = field;
        });
    }
};
