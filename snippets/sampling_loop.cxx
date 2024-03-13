// read the entire dictionary.txt
while( inputfile >> str ) {
	// should we use it for the experiment?
	if( bernoulli(p) ) {

		/** save str for testing, maybe in a container named words?  **/

		// should it go into the table?
		if( bernoulli(0.5) ) {
			table.insert(str)
		}
	}
}
