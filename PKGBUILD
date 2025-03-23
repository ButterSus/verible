# Maintainer: poscat
# Modified for ButterSus fork

pkgname=verible-buttersus-git
pkgver=0.0.r3946.g851d3ff4
pkgrel=1
pkgdesc="Suite of SystemVerilog developer tools with enhanced port alignment features (ButterSus fork)"
arch=('x86_64' 'aarch64')
url='https://github.com/ButterSus/verible'
license=('Apache 2.0')
depends=('bash')
makedepends=('python' 'bazel' 'git' 'm4' 'flex' 'bison')
provides=('verible')
conflicts=('verible' 'verible-git' 'verible-bin')
source=("git+https://github.com/ButterSus/verible.git")
sha256sums=('SKIP')

pkgver() {
  cd "${srcdir}/verible"
  git describe --long | sed 's/\([^-]*-g\)/r\1/;s/-/./g;s/v//g'
}

build() {
  cd "${srcdir}/verible" || (
    echo -e "\E[1;31mCan't change working directory to ${srcdir}/verible! Build Failed!\E[0m"
    exit 1
  )

  bazel build -c opt --//bazel:use_local_flex_bison //:install-binaries
}

check() {
  cd "${srcdir}/verible" || (
    echo -e "\E[1;31mCan't change working directory to ${srcdir}/verible! Check Failed!\E[0m"
    exit 1
  )

  # Only run basic tests to save time
  bazel test -c opt --//bazel:use_local_flex_bison //verible/verilog/tools/formatter:verible-verilog-format_test
}

package() {
  cd "${srcdir}/verible" || (
    echo -e "\E[1;31mCan't change working directory to ${srcdir}/verible! Package Failed!\E[0m"
    exit 1
  )

  .github/bin/simple-install.sh "${pkgdir}/usr/bin"
} 