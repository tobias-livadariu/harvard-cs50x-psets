function buyShovel() {
    fetch('/buyShovel', {
        method: 'POST',
    })
    .then(response => response.json())
    .then(data => {
        shovelButton = document.getElementById('shovel-button')
        curShovel = data.curShovel
        maxShovel = data.maxShovel
        shovels = data.shovels
        shovelCost = data.shovelCost

        if (curShovel < maxShovel)
        {
            shovelButton.textContent = "Forge a {{ shovels[curShovel + 1] }} shovel (cost: {{ shovelCost }} skeletons)"
        }
    });
}
