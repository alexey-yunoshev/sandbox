Why:
- reduce latency
- reduce traffic

Kinds:
- browser
- proxy (shared cache)
- gateway caches

## Headers

Expires: Fri, 30 Oct 1998 14:19:41 GMT

__Cache-Control__
Addresses the limitations of _Expires_

When both Cache-Control and Expires are present, Cache-Control takes precedence.

__max-age__ - duh

__s-maxage__ - max-age for proxies

__public__ - authenticated pages may be cached in proxies

__private__ - no proxies

__no-cache__ — validate every time.

__no-store__ - do not cache at all

__must-revalidate__ — obey any freshness information

__proxy-revalidate__ — must-revalidate for proxy

Example:
`Cache-Control: max-age=3600, must-revalidate`

## Validators

Etag + If-None-Match

Last-Modified + If-Modified-Since