function autoEdit(api) {
    var posRef = api.input.documentEndAnchor();
    posRef = api.input.positionRelativeTo(posRef, "backward", 1);
    api.input.setSelectedTextRange(posRef, posRef);

/*    var posRef = api.input.documentStartAnchor();
    posRef = api.input.positionRelativeTo(posRef, "forward", 11);
    api.input.setSelectedTextRange(posRef, posRef);*/

    api.cursor.enterPressed();
    api.cursor.insertCharacter("Puff, the magic dragon, lives by the sea.");
}
