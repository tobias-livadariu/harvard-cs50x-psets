/* Like in the python function found within helpers.py,
the purpose of this function is to shrink numbers
based on their size using suffixes. */
function formatNumberSuffix(num) {
    if (num >= 1_000_000_000_000_000_000_000_000_000) {
        return (num / 1_000_000_000_000_000_000_000_000_000).toFixed(2) + 'o';
    } else if (num >= 1_000_000_000_000_000_000_000_000) {
        return (num / 1_000_000_000_000_000_000_000_000).toFixed(2) + 'S';
    } else if (num >= 1_000_000_000_000_000_000_000) {
        return (num / 1_000_000_000_000_000_000_000).toFixed(2) + 's';
    } else if (num >= 1_000_000_000_000_000_000) {
        return (num / 1_000_000_000_000_000_000).toFixed(2) + 'Q';
    } else if (num >= 1_000_000_000_000_000) {
        return (num / 1_000_000_000_000_000).toFixed(2) + 'q';
    } else if (num >= 1_000_000_000_000) {
        return (num / 1_000_000_000_000).toFixed(2) + 't';
    } else if (num >= 1_000_000_000) {
        return (num / 1_000_000_000).toFixed(2) + 'b';
    } else if (num >= 1_000_000) {
        return (num / 1_000_000).toFixed(2) + 'm';
    } else if (num >= 1_000) {
        return (num / 1_000).toFixed(2) + 'k';
    } else {
        return num.toString();
    }
};
