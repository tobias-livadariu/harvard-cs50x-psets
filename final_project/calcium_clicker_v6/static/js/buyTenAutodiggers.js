function buyTenAutodiggers() {
    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        /* Getting the max number of autodiggers the user can buy. */
        numAutodiggersBuyable = data.numAutodiggersBuyable
        if (numAutodiggersBuyable < 10) {
            throw new Error("10x transaction failed")
        }

        /* Buying 10 autodiggers for the user. */
        for (var i = 0; i < 10; i++) {

        }
    })
    .catch(error => {
        console.error("Error during purchase:", error);
    });
}
