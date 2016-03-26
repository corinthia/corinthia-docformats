function insertParagraph(str) {
    for (var i = 0; i < str.length; i++) {
        api.cursor.insertCharacter(str[i]);
    }
    api.cursor.enterPressed();
}

function autoEdit(api) {
    insertParagraph("New Shiny Header");
}
