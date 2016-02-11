#include <WS2tcpip.h>
#include <errno.h>
#include "neterror.h"

DWORD wsa_errno = 0;

void neterror()
{
    wsa_errno = WSAGetLastError();
    switch (wsa_errno) {
    case WSAEWOULDBLOCK:
        errno = EWOULDBLOCK;
        break;
    case WSAEINPROGRESS:
        errno = EINPROGRESS;
        break;
    case WSAEALREADY:
        errno = EALREADY;
        break;
    case WSAENOTSOCK:
        errno = ENOTSOCK;
        break;
    case WSAEDESTADDRREQ:
        errno = EDESTADDRREQ;
        break;
    case WSAEMSGSIZE:
        errno = EMSGSIZE;
        break;
    case WSAEPROTOTYPE:
        errno = EPROTOTYPE;
        break;
    case WSAENOPROTOOPT:
        errno = ENOPROTOOPT;
        break;
    case WSAEPROTONOSUPPORT:
        errno = EPROTONOSUPPORT;
        break;
    //case WSAESOCKTNOSUPPORT:
    //    errno = ESOCKTNOSUPPORT;
    //    break;
    case WSAEOPNOTSUPP:
        errno = EOPNOTSUPP;
        break;
    //case WSAEPFNOSUPPORT:
    //    errno = EPFNOSUPPORT;
    //    break;
    case WSAEAFNOSUPPORT:
        errno = EAFNOSUPPORT;
        break;
    case WSAEADDRINUSE:
        errno = EADDRINUSE;
        break;
    case WSAEADDRNOTAVAIL:
        errno = EADDRNOTAVAIL;
        break;
    case WSAENETDOWN:
        errno = ENETDOWN;
        break;
    case WSAENETUNREACH:
        errno = ENETUNREACH;
        break;
    case WSAENETRESET:
        errno = ENETRESET;
        break;
    case WSAECONNABORTED:
        errno = ECONNABORTED;
        break;
    case WSAECONNRESET:
        errno = ECONNRESET;
        break;
    case WSAENOBUFS:
        errno = ENOBUFS;
        break;
    case WSAEISCONN:
        errno = EISCONN;
        break;
    case WSAENOTCONN:
        errno = ENOTCONN;
        break;
    //case WSAESHUTDOWN:
    //    errno = ESHUTDOWN;
    //    break;
    //case WSAETOOMANYREFS:
    //    errno = ETOOMANYREFS;
    //    break;
    case WSAETIMEDOUT:
        errno = ETIMEDOUT;
        break;
    case WSAECONNREFUSED:
        errno = ECONNREFUSED;
        break;
    case WSAELOOP:
        errno = ELOOP;
        break;
    case WSAENAMETOOLONG:
        errno = ENAMETOOLONG;
        break;
    //case WSAEHOSTDOWN:
    //    errno = EHOSTDOWN;
    //    break;
    case WSAEHOSTUNREACH:
        errno = EHOSTUNREACH;
        break;
    case WSAENOTEMPTY:
        errno = ENOTEMPTY;
        break;
    //case WSAEPROCLIM:
    //    errno = EPROCLIM;
    //    break;
    //case WSAEUSERS:
    //    errno = EUSERS;
    //    break;
    //case WSAEDQUOT:
    //    errno = EDQUOT;
    //    break;
    //case WSAESTALE:
    //    errno = ESTALE;
    //    break;
    //case WSAEREMOTE:
    //    errno = EREMOTE;
    //    break;
    }
}
