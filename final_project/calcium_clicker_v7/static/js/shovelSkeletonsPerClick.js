// JavaScript function for determining the number of skeletons per click each shovel provides
function shovelSkeletonsPerClick(curShovel, baseValue = 1, polyPower = 1.75, exponentialKicker = 1.08) {
    return Math.floor(baseValue * Math.pow((curShovel + 1), polyPower) * Math.pow(exponentialKicker, Math.sqrt(curShovel + 1)));
}
