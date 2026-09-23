# Source - https://stackoverflow.com/a/645318
# Posted by Nick Presta, modified by community. See post 'Timeline' for change history
# Retrieved 2026-08-31, License - CC BY-SA 4.0

import re
import requests

source_url = "http://challenge01.root-me.org/programmation/ch1/"
destination_url = "http://challenge01.root-me.org/programmation/ch1/ep1_v.php?result="

session = requests.Session()

r = session.get(source_url)
text = r.text

deli = re.search(r"U<sub>(\d+)</sub>", text)

un = 2
u0 = 3

print(deli)

