function insertParagraph(str) {
    for (var i = 0; i < str.length; i++) {
        api.cursor.insertCharacter(str[i]);
    }
    api.cursor.enterPressed();
}

function moveRight(num) {
    for (var i = 0; i < num; i++) {
        api.cursor.moveRight();
    }
    api.cursor.enterPressed();
}

function autoEdit(api) {
    moveRight(33);
    api.cursor.enterPressed();
    insertParagraph("New Shiny Paragraph");
}
