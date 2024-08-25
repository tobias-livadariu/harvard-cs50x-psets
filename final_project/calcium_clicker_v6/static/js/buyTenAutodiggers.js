function buyTenAutodiggers() {
    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        /* Getting the number of errors  */
        numAutodiggersBuyable = data.numAutodiggersBuyable
        if (numAutodiggersBuyable > 10) {
            throw new Error("10x transaction failed")
        }
    })
    .catch(error => {
        console.error("Error during purchase:", error);
    });
}
