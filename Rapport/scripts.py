import matplotlib.pyplot as plt
import numpy as np
import csv

def fixfilsti(filsti):
    return filsti.replace("\\" , "/")

def opnefil(filsti):
    csvfil = []
    time = []
    channel1 = []
    channel2 = []
    
    with open(filsti , newline='') as fil:
        csvreader = csv.reader(fil)
        for row in csvreader:
            time.append(float(row[0]))
            channel1.append(float(row[1]))
            channel2.append(float(row[2]))

    return time , channel1 , channel2

def plott(filsti):
    tid , kanal1 , kanal2 = opnefil(filsti)
    
    plt.figure()
    
    plt.plot(tid , kanal2 , label = 'Kanal 2' , color="blue")
    plt.plot(tid , kanal1 , label = 'Kanal 1' , color="orange")
    
    plt.xlabel("Tid [s]")
    plt.ylabel("Spenning [V]")
    plt.legend()
    plt.show()
    
print(fixfilsti(r"C:\Users\vetle\OneDrive\Skolegang\Universitet\Elektronisk systemdesign & innovasjon\2. Semester\TTT4160 Elektronisk systemdesign & analyse 1\Øvinger\Oving4\Bilder\Oppgave5A_amplituderespons.png"))
#plott(r"C:\Users\vetle\OneDrive\Skolegang\Universitet\Elektronisk systemdesign & innovasjon\2. Semester\TTT4160 Elektronisk systemdesign & analyse 1\Øvinger\Oving4\CSVfiler\Oppgave2C.csv")

def plottamp(R , f , type , C = 0 , L = 0):
    amp = []
    phase = []
    
    
    if type == "RC":
        for i in range(len(f)):
            phase.append(np.arctan(R*C*np.pi*2*f[i]))
            amp.append((np.sqrt(1 + (R*C*2*np.pi*f[i])**2))/((R*C*f*2*np.pi)**2 + 1))
    
    
    plt.figure()
    plt.plot(f , amp , label="amplitude" , color = "blue")
    plt.xlabel("Frekvens[Hz]")
    plt.ylabel("Spenning[V]")
    plt.legend()
    plt.title("Amplitude")
    
    plt.figure()
    plt.plot(f , amp , label="fase" , color = "red")
    plt.xlabel("Frekvens[Hz]")
    plt.ylabel("Forskyvning[rad]")
    plt.legend()
    plt.title("Fase")
    
    plt.show()
    
def PlottKompleksfunksjon():
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Eksempeldata
    x = np.linspace(0, 2*np.pi, 100)
    y = np.sin(x)
    z = np.cos(x)

    # Plott data
    ax.plot(x, y, z, label="3D-kurve")
    ax.legend()

    # Sett aksene til å starte i origo
    ax.set_xlim([0, 6])  # X-akse
    ax.set_ylim([-1, 1])  # Y-akse
    ax.set_zlim([-1, 1])  # Z-akse
    
    
    
    ax.plot([0, 0], [ax.get_ylim()[0], ax.get_ylim()[1]], [0, 0], color="black")  # Y-akse
    ax.plot([ax.get_xlim()[0], ax.get_xlim()[1]], [0, 0], [0, 0], color="black")  # X-akse
    ax.plot([0, 0], [0, 0], [ax.get_zlim()[0], ax.get_zlim()[1]], color="black")  # Z-akse

    
    ax.set_box_aspect([1, 1, 1])

    # Legg til aksetitler
    ax.set_xlabel("X-akse")
    ax.set_ylabel("Y-akse")
    ax.set_zlabel("Z-akse")

    plt.show()

PlottKompleksfunksjon()
    
    
    
    
    