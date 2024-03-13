double tests = 0;
double comparisons = 0;
/** for every word in the experiment (not every word in dictionary.txt!) **/
for( string str: words ) {
	// should we use it for testing?
	if( bernoulli( 1000.0/words.size() ) ) {
		tests++;
		comparisons += table.contains(str);
	}
}
