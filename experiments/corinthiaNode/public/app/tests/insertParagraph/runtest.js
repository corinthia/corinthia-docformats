function moveRight(num) {
    for (var i = 0; i < num; i++) {
        api.cursor.moveRight();
    }
}

function autoEdit(api) {
    moveRight(14);
    var frmt = api.formatting.getFormatting();
    moveRight(21);
    api.cursor.enterPressed();
    api.cursor.insertCharacter("New Shiny Paragraph");
    api.formatting.applyFormattingChanges(frmt["-corinthia-paragraph-style"],{});
}
