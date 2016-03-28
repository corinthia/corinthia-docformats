function autoEdit(api) {
    //don't like this but it works
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.enterPressed();
    api.cursor.insertCharacter("Puff, the magic dragon, lives by the sea.");
    api.cursor.enterPressed();
    api.cursor.insertCharacter("This should be almost at the end.");
    api.cursor.enterPressed();
    api.cursor.insertCharacter("This should be at the end.");
}
