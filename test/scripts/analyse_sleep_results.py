import argparse
import pandas as pd
import os
import re

RESULTS_DIR : str = '../results/'
DURATION_REGEX : re.Pattern = re.compile('-([0-9]+)([a-zA-Z]*[sS])\\.')
UNIT_TO_NS : dict[str, float] = {
	's'		: 1000000000.0,
	'ms'	: 1000000.0,
	'us'	: 1000.0,
	'ns'	: 1.0,
}
UNIT_TO_S : dict[str, float] = {
	'ns'	: 1000000000.0,
	'us'	: 1000000.0,
	'ms'	: 1000.0,
	's'		: 1.0,
}

if __name__ == '__main__':
	parser = argparse.ArgumentParser(
						prog='Analyse Sleep Results Script',
						description='This program analyses and amalgamates the results of the sleep unit tests.')
	parser.add_argument('-a', '--accumulate', action='store_true')
	args = parser.parse_args()

	results : list[dict] = []
	for name in os.listdir(RESULTS_DIR):
		if os.path.isfile(RESULTS_DIR + name) and name.split('.')[-1] == 'csv':
			matches = DURATION_REGEX.search(name)
			if matches and len(matches.groups()) == 2:
				results.append({
					'name' : name,
					'path' : RESULTS_DIR + name,
					'amount' : float(matches.group(1)),
					'unit' : matches.group(2)
				})

	all_summary : pd.DataFrame = pd.DataFrame(columns = ['Name', 'Requested ns', 'Mean ns', 'Standard Deviation ns', 'Minimum ns', 'Maximum ns', 'Mean Error ns'])
	
	if args.accumulate:
		writer = pd.ExcelWriter(RESULTS_DIR + 'all.xlsx', 'openpyxl', mode='w')
	
	for i, r in enumerate(results):
		print(r['name'])
		df = pd.read_csv(r['path'])
		df['Difference ns'] = df['End'] - df['Start']
		all_summary.loc[i] = [
			r['name'], 
			r['amount'] * UNIT_TO_NS[r['unit']], 
			df['Difference ns'].mean(), 
			df['Difference ns'].std(), 
			df['Difference ns'].min(),
			df['Difference ns'].max(),
			df['Difference ns'].mean() - r['amount'] * UNIT_TO_NS[r['unit']]
		]

		if args.accumulate:
			df.to_excel(writer, sheet_name=r['name'], index=False)

	if args.accumulate:
		writer.close()

	all_summary.sort_values(['Requested ns', 'Name'], ascending = True, inplace = True)
	all_summary.to_csv(RESULTS_DIR + 'all-summary.csv', index = False)