function autoEdit(api) {
    var posRef = api.input.documentStartAnchor();
    api.input.setSelectedTextRange(posRef, posRef);
    var frmt = api.formatting.getFormatting();
    api.cursor.enterPressed();
    api.cursor.moveLeft();
    api.cursor.insertCharacter("New Shiny Header");
    api.formatting.applyFormattingChanges(frmt["-corinthia-paragraph-style"],{});
}
