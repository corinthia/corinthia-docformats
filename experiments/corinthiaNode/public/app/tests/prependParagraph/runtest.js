function autoEdit(api) {
    var posRef = api.input.documentStartAnchor();
    api.input.setSelectedTextRange(posRef, posRef);
    api.cursor.enterPressed();
    api.cursor.moveLeft();
    api.cursor.insertCharacter("Puff the magic dragon lives by the sea.");
}
