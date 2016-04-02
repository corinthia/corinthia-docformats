function autoEdit(api) {
    var posRef = api.input.documentStartAnchor();
    api.input.setSelectedTextRange(posRef, posRef);
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.moveRight();
    api.cursor.insertCharacter(" One And The Only");
    autosave = false;
}
