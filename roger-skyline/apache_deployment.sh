#!/bin/sh

# Checks if Apache2 is running
if ps -ef | grep -q apache2
then
	echo 'Apache2 service is already running'
else
	sudo systemctl start apache2
fi

sudo bash -c "mkdir -p /var/www/html/mywebsite.com"
sudo bash -c "echo '<html>
  <body>
    <center><h1>This is my website!</h1></center>
  </body>
</html>' >> /var/www/html/mywebsite.com/index.html"

# Changes ownership of /var/www/html to www-data
sudo chown -R www-data: /var/www/html

# Creates a Virtual Host File for our website
echo "Port 2525 is chosen arbitrarily for Apache Reverse Proxy"
sudo bash -c "echo '<VirtualHost *:80>

ServerName mywebsite.com
Redirect Permanent / "https://10.0.2.3/"

</VirtualHost>

<VirtualHost *:443>

ServerAdmin admin@mywebsite.com
ServerName mywebsite.com
ServerAlias www.mywebsite.com
DocumentRoot /var/www/html/mywebsite.com

SSLEngine On
SSLCertificateFile /etc/ssl/certs/apache-selfsigned.crt
SSLCertificateKeyFile /etc/ssl/private/apache-selfsigned.key

ProxyPreserveHost On
ProxyRequests Off
SSLProxyEngine On
ProxyPass / http://localhost:2525/
ProxyPassReverse / http://localhost:2525/

ErrorLog /mywebsite.com_error.log
</VirtualHost>' >> /etc/apache2/sites-available/mywebsite.com.conf"

# Enables the Virtual Host
sudo a2ensite mywebsite.com.conf

# For this to work, Apache needs to be reloaded
sudo systemctl reload apache2

# Generate SSL self-signed certificate & key
sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/apache-selfsigned.key -out /etc/ssl/certs/apache-selfsigned.crt

# Generate a strong Diffie-Hellman group
sudo openssl dhparam -out /etc/ssl/certs/dhparam.pem 2048

# Create the SSL params file
sudo bash -c "echo -e '# from https://cipherli.st/
# and https://raymii.org/s/tutorials/Strong_SSL_Security_On_Apache2.html

SSLCipherSuite EECDH+AESGCM:EDH+AESGCM:AES256+EECDH:AES256+EDH
SSLProtocol All -SSLv2 -SSLv3
SSLHonorCipherOrder On
# Disable preloading HSTS for now.  You can use the commented out header line that includes
# the \x22preload\x22 directive if you understand the implications.
#Header always set Strict-Transport-Security \x22max-age=63072000; includeSubdomains; preload\x22
Header always set Strict-Transport-Security \x22max-age=63072000; includeSubdomains\x22
Header always set X-Frame-Options DENY
Header always set X-Content-Type-Options nosniff
# Requires Apache >= 2.4
SSLCompression off 
SSLSessionTickets Off
SSLUseStapling on 
SSLStaplingCache \x22shmcb:logs/stapling-cache(150000)\x22

SSLOpenSSLConfCmd DHParameters \x22/etc/ssl/certs/dhparam.pem\x22' >> /etc/apache2/conf-available/ssl-params.conf"

# Make a backup of the default-SSL conf
sudo cp /etc/apache2/sites-available/default-ssl.conf /etc/apache2/sites-available/default-ssl.conf.bak

# Remove commented lines from default-SSL conf
sudo sed -i '/^\t\t#/d' /etc/apache2/sites-available/default-ssl.conf

# Edit few things in default-SSL conf
sudo sed -i '/ServerAdmin/a \\t\tServerAdmin admin@mywebsite.com\n\t\tServerName mywebsite.com' /etc/apache2/sites-available/default-ssl.conf
sudo sed -i '/ServerAdmin webmaster/d' /etc/apache2/sites-available/default-ssl.conf
sudo sed -i '/SSLCertificateFile/a \\t\tSSLCertificateFile\t/etc/ssl/certs/apache-selfsigned.crt\n\t\tSSLCertificateKeyFile /etc/ssl/private/apache-selfsigned.key' /etc/apache2/sites-available/default-ssl.conf
sudo sed -i '/snakeoil/d' /etc/apache2/sites-available/default-ssl.conf
sudo sed -i '/<\/Directory>/a \\n\t\tBrowserMatch "MSIE [2-6]" \\\n\t\t\t\tnokeepalive ssl-unclean-shutdown \\\n\t\t\t\tdowngrade-1.0 force-response-1.0' /etc/apache2/sites-available/default-ssl.conf

# Enable ssl, headers, proxy, proxy_http mods
sudo a2enmod ssl
sudo a2enmod headers
sudo a2enmod proxy
sudo a2enmod proxy_http

# Enable SSL Virtual Host
sudo a2ensite default-ssl

# Enable ssl-params conf
sudo a2enconf ssl-params

# Restart Apache service
sudo systemctl restart apache2

echo "Don't forget to add HTTP port forwarding in VirtualBox.
ex: Host: 127.0.0.1:8080 Guest: ip:80"
