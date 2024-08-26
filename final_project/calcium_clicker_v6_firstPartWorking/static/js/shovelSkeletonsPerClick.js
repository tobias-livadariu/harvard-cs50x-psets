// JavaScript function for determining the number of skeletons per click each shovel provides
function shovelSkeletonsPerClick(curShovel, baseValue = 10, polyPower = 1.5, exponentialKicker = 1.02) {
    return Math.floor(baseValue * Math.pow((curShovel + 1), polyPower) * Math.pow(exponentialKicker, Math.sqrt(curShovel + 1)));
}
