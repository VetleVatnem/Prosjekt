import csv

def add_column_to_csv(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
        reader = csv.reader(infile)
        writer = csv.writer(outfile)
        i = 0
        for row_index, row in enumerate(reader):
            if i == 20000:
                break
            # Legg til en ny kolonneverdi (f.eks. en indeks)
            new_column_value = row_index * 1/44100
            # Skriv den nye raden med den ekstra kolonnen
            writer.writerow([new_column_value] + row)
            i += 1

# Bruk funksjonen
input_path = r"C:\Users\vetle\Documents\Math4C\ESDAlydfil.csv"
output_path = r"C:\Users\vetle\Documents\Math4C\ESDAlydfil_with_column.csv"
add_column_to_csv(input_path, output_path)