# ISA Projekt - Monitorování DHCP komunikace

        Author:  Maksim Kalutski (xkalut00)
        Date:    2023-11-17

## Úvod

Aplikace je navržena jako konzolová aplikace s možností sledování v reálném čase nebo analýzy existujících souborů. 
Program zpracovává pakety přenášené po síti a aktualizuje statistiky pro každý definovaný IP prefix. V případě, že
překročí 50% alokací, program informuje uživatele o tomto faktu.

## Teorie

Dynamic Host Configuration Protocol (DHCP) je síťový protokol používaný pro automatickou konfiguraci IP adres a dalších
síťových parametrů v počítačových sítích. Jeho hlavním cílem je zjednodušit a automatizovat proces přidělování síťových
konfigurací zařízením v síti, což zahrnuje přidělování IP adres, brány, DNS serverů a dalších informací potřebných pro
správnou komunikaci na síti.

DHCP výrazně usnadňuje správu sítě tím, že eliminuje potřebu ruční konfigurace síťových parametrů na každém zařízení.
Zároveň umožňuje efektivní využívání dostupných IP adres v síti a umožňuje jednoduchou adaptaci na změny v konfiguraci
sítě.
## Předpoklady

Před použitím programu musíte mít v operačním systému **UNIX** nainstalovány **g++**, **make**, **ncurses** a **libpcap**.

Pro **OS unixového typu**, můžete nainstalovat `g++` a `make` spuštěním následujícího příkazu:

```console
$ sudo apt-get install build-essential
```

Pro instalaci `ncurses` do systému spusťte následující příkaz:

```console
$ sudo apt-get install libncurses5-dev libncursesw5-dev
```

Pro instalaci `libpcap` do systému spusťte následující příkaz:

```console
$ sudo apt install libpcap-dev
```

## Sestavení programu

Pro sestavení programu spusťte následující příkaz:

```console
$ make
```

## Použití

```console
./dhcp-stats [-r <filename>] [-i <interface-name>] <ip-prefix> [ <ip-prefix> [ ... ] ]
```

### Argumenty příkazového řádku

| Argument    | Popis                                               |
|-------------|-----------------------------------------------------|
| `-i`        | Rozhraní, na kterém může program naslouchat.        |
| `-r`        | Statistika bude vytvořena z pcap souborů.           |
| `ip-prefix` | Rozsah sítě pro které se bude generovat statistika. |

## Příklady Použití

```console
$ sudo ./dhcp-stats -i lo 192.168.1.0/24 192.168.0.0/22 172.16.32.0/24
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.0.0/22 1022 123 12.04%
192.168.1.0/24 254 123 48.43%
172.16.32.0/24 254 15 5.9%
```

```
$ ./dhcp-stats -r dhcp.pcapng 192.168.1.0/24 172.16.32.0/24
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/24 254 50 19.69%
172.16.32.0/24 254 0 0.00%
```

## Knihovny

Program používá následující knihovny:

- `<iostream>`: Poskytuje vstupně-výstupní streamy pro vstup a výstup.

- `<arpa/inet.h>`: Obsahuje funkce pro manipulaci s internetovými adresami a konverze mezi textovými a binárními
  formáty.

- `<pcap/pcap.h>`: Poskytuje funkce pro zachytávání síťových paketů.

- `<cstdlib>`: Poskytuje obecné funkce pro manipulaci s pamětí a běžné funkce.

- `<netinet/ip.h>`: Obsahuje definici struktury pro IPv4 hlavičku.

- `<netinet/udp.h>`: Obsahuje definici struktury pro UDP hlavičku.

- `<netinet/ether.h>`: Obsahuje definice pro práci s ethernetovými rámci.

- `<map>`: Poskytuje implementaci asociativního kontejneru typu map.

- `<ncurses.h>`: Poskytuje funkce pro tvorbu textového uživatelského rozhraní v terminálu.

- `<syslog.h>`: Poskytuje funkce pro zápis do systémového logu.

- `<getopt.h>`: Poskytuje funkce pro zpracování příkazové řádky.

- `<cstring>`: Poskytuje funkce pro manipulaci s řetězci.

- `<vector>`: Poskytuje implementaci dynamického pole.

- `<stdexcept>`: Poskytuje vyjímky pro běhové chyby.

- `<algorithm>`: Poskytuje algoritmické funkce pro práci s kontejnery.

- `<signal.h>`: Poskytuje funkce pro zachytávání a zpracování signálů.

- `<unistd.h>`: Obsahuje funkce pro práci s POSIX systémovými voláními.

## Komponenty programu

Program obsahuje následující funkce a struktury:
### Struktury

- `PrefixStats`: Slouží k uchování statistik týkajících se IP adresového prefixu. Obsahuje samotný prefix, maximální počet hostitelů, přidělené adresy a využití.
- `Options`: Obsahuje programové volby, včetně síťového rozhraní, názvu souboru pro pcap soubory, seznamu IP adresových prefixů a mapy statistik prefixů.
- `UserData`: Slouží k předání dat do funkce `packetHandler` pro použití s pcap smyčkou.

### Funkce

- `initNcurses()` a `endNcurses()`: Inicializuje a ukončuje knihovnu ncurses pro zobrazení statistik v terminálu.
- `handleSignal()`: Ovladač signálů pro zpracování SIGINT (CTRL-C) a elegantní ukončení programu.
- `displayPrefixStats()`: Vypisuje statistiky pro daný IP adresový prefix.
- `printOptions()`: Vypisuje celkové programové volby a seřazené statistiky prefixů IP adres.
- `printUsage()`: Vypisuje návod k použití programu.
- `parseArguments()`: Zpracovává argumenty příkazové řádky a naplňuje strukturu Options.
- `calculateMaxHosts()`: Spočítá maximální počet hostitelů pro daný IP adresový prefix.
- `updateStats()`: Aktualizuje statistiky pro daný IP adresový prefix na základě přidělených adres.
- `updateNcurses()`: Aktualizuje zobrazení ncurses nejnovějšími statistikami.
- `processPacket()`: Zpracovává individuální paket, aktualizuje statistiky, pokud odpovídá IP adresovému prefixu.
- `packetHandler()`: Ovladač paketů pro použití s pcap smyčkou, volá funkci processPacket.
- `processPcapngFile()`: Zpracovává pakety z pcapng souboru, aktualizuje statistiky.
- `captureLivePackets()`: Zachytává živé pakety ze síťového rozhraní, aktualizuje statistiky v reálném čase.

## Popis implementace

### Zpracování argumentů

Funkce `parseArguments` slouží k parsování příkazové řádky. Podporuje zadání síťového rozhraní (`-i`) nebo názvu souboru (`-r`). Argumenty obsahující IP prefixy jsou uloženy v struktuře `Options`.

### Zpracování paketů

Funkce `processPacket` analyzuje příchozí síťový paket. Kontroluje, zda se jedná o IP paket a následně porovnává zdrojovou
IP adresu s definovanými prefixy. Aktualizuje statistiky v `Options`.

### Ncurses a aktualizace v reálném čase

Při sledování síťového rozhraní v reálném čase je použita knihovna `ncurses` pro vytvoření dynamického výstupu. Funkce
`updateNcurses` pravidelně aktualizuje obrazovku s aktuálními statistikami.

### Zpracování pcapng souboru

Funkce `processPcapngFile` zpracovává pcapng soubor. Otevře soubor, inicializuje ncurses a spouští zpracování paketů
pomocí `pcap_loop`. Následně aktualizuje statistiky a uzavře soubor.

### Sledování síťového rozhraní v reálném čase

Funkce `captureLivePackets` otevírá živý odposlouchávací režim na zadaném síťovém rozhraní. Zpracovává pakety ve smyčce a
aktualizuje statistiky v reálném čase. Reaguje na přerušení signálem `SIGINT`.

### Hlavní funkce main

Hlavní funkce `main` začíná parsováním argumentů a inicializací syslogu. Podle režimu (rozhraní nebo soubor) volí
odpovídající funkci. Po dokončení zobrazí výsledné statistiky a případná varování syslogu.


# **Testování**

Program byl testován na **[Windows Subsystem for Linux 2 (WSL2)](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux)**
se systémem **Ubuntu 22.04.1 LTS** a na **Merlinu**. Pro testování byly použity soubory pcap z adresáře `tests` a
síťové rozhraní `lo`. Program byl testován na různých scénářích, včetně přímého zachycení sítě i rozboru souborů pcap. 
Abych otestoval, zda program správně zachycuje DHCP provoz z rozhraní `lo`, spustil jsem ve druhém terminálu příkaz `tcpreplay` s různými soubory pcap.
Výsledky testů jsou uvedeny níže.

## Spuštění testů:
Otevřete terminál a zkompilujte program pomocí příkazu `make`. Po dokončení kompilace spusťte program pomocí 
příkazu `./dhcp-stats` s argumenty příkazového řádku.

## Sekce 1: Monitorování DHCP provozu na specifikovaném rozhraní

### Test 1: Monitorování DHCP provozu na rozhraní lo

#### Vstup:

```console
$ sudo ./dhcp-stats -i lo 192.168.1.0/26 172.16.32.0/24 192.168.0.0/22
```

#### Očekávaný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/26 62 20 32.26%
192.168.0.0/22 1022 22 2.15%
172.16.32.0/24 254 0 0.00%
```

#### Skutečný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/26 62 20 32.26%
192.168.0.0/22 1022 22 2.15%
172.16.32.0/24 254 0 0.00%
```

### Test 2: Monitorování DHCP provozu na rozhraní lo s překročením 50% využití

#### Vstup:

```console
$ sudo ./dhcp-stats -i lo 192.168.1.0/26 172.16.32.0/24 192.168.0.0/22
```

#### Očekávaný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/26 62 50 80.65%
192.168.0.0/22 1022 50 4.89%
172.16.32.0/24 254 0 0.00%
prefix 192.168.1.0/26 exceeded 50% of allocations .
```

#### Skutečný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/26 62 50 80.65%
192.168.0.0/22 1022 50 4.89%
172.16.32.0/24 254 0 0.00%
prefix 192.168.1.0/26 exceeded 50% of allocations .
```

## Sekce 2: Monitorování DHCP provozu z pcap souboru

### Test 3: Monitorování DHCP provozu ze souboru dhcp-ack-second.pcapng

#### Vstup:

```console
$ ./dhcp-stats -r tests/dhcp-ack-second.pcapng 192.168.1.0/24 192.168.0.0/22 172.16.32.0/24
```

#### Očekávaný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/24 254 20 7.87%
192.168.0.0/22 1022 20 1.96%
172.16.32.0/24 254 0 0.00%
```

#### Skutečný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/24 254 20 7.87%
192.168.0.0/22 1022 20 1.96%
172.16.32.0/24 254 0 0.00%
```

### Test 4: Monitorování DHCP provozu ze souboru dhcp-ack-random.pcapng s překročením 50% využití

#### Vstup:

```console
$ ./dhcp-stats -r tests/dhcp-ack-random.pcapng 192.168.1.0/26 172.16.32.0/24 192.168.0.0/22
```

#### Očekávaný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/26 62 50 80.65%
192.168.0.0/22 1022 50 4.89%
172.16.32.0/24 254 0 0.00%
prefix 192.168.1.0/26 exceeded 50% of allocations .
```

#### Skutečný výstup:

```console
IP-Prefix Max-hosts Allocated addresses Utilization
192.168.1.0/26 62 50 80.65%
192.168.0.0/22 1022 50 4.89%
172.16.32.0/24 254 0 0.00%
prefix 192.168.1.0/26 exceeded 50% of allocations .
```

## Závěr

Program úspěšně monitoruje provoz DHCP, analyzuje přidělené IP adresy a vypočítává využití zadaných síťových prefixů.
Poskytuje aktualizace v reálném čase pomocí ncurses a zaznamenává zprávy prostřednictvím mechanismu syslog, pokud
využití překročí 50 %. Program byl testován na různých scénářích, včetně přímého zachycení sítě i rozboru souborů pcap,
a prokázal přesné a spolehlivé výsledky.

## Literatura

[1] RFC 2131: "Dynamic Host Configuration Protocol.": https://datatracker.ietf.org/doc/html/rfc2131

[2] Beej's Guide to Network Programming http://beej.us/guide/bgnet/

[3] Manuál k funkcím pcap: https://www.tcpdump.org/manpages/pcap.3pcap.html

[4] Manuál k funkcím syslog: https://man7.org/linux/man-pages/man3/syslog.3.html

[5] Manuál k funkcím ncurses: https://invisible-island.net/ncurses/man/ncurses.3x.html

[6] Ncurses Documentation: https://invisible-island.net/ncurses/ncurses-intro.html
