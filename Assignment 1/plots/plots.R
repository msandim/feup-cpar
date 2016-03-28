library(ggplot2)
library(grid)
library(dplyr)
library(RColorBrewer)
library(reshape)

# Open file:
file <- read.csv("output_24_mar_O3_fcup.csv", header = FALSE)
names(file) <- c("lang", "alg", "threads", "N", "time", "l1", "l2")

# Number of operations:
file <- mutate(file, n_oper = 2*(N^3)) # Número de operações
file <- mutate(file, flops = n_oper/time) # Flops
file <- mutate(file, gflops = flops/1000000000) # GigaFlops
file <- mutate(file, ratioL1 = l1/n_oper)
file <- mutate(file, ratioL2 = l2/n_oper)
file <- mutate(file, alg = ifelse(alg == 'Mult', 'Alg 1', 'Alg 2'))

# C++:
cpp_mult_3000 <- file[1:7,]
cpp_line_3000 <- file[15:21,]

cpp_line_10000 <- file[29:32,]

cpp_mult_par <- file[33:60,]
cpp_line_par <- file[61:88,]

# Java
java_mult_3000 <- file[8:14,]
java_line_3000 <- file[22:28,]

# 1 - Language differences
# 1.1 - Execution time
data1 <- rbind(cpp_mult_3000, cpp_line_3000, java_mult_3000, java_line_3000)
data1 <- filter(data1)

p1.1 <- ggplot(data1, aes(x=N, y=time, color=paste(lang, alg))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="Tempo de execução (s)") +
  scale_color_discrete(name=NULL) +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm")) +
ggsave("plot1_1.pdf", width=9, height=3)

# 1.2 - GFLOPs
p1.2 <- ggplot(data1, aes(x=N, y=gflops, color=paste(lang, alg))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="GFPLOP/s") +
  scale_color_discrete(name=NULL) +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"))
ggsave("plot1_2.pdf", width=9, height=3)


# 2 - Cache differences
data2 <- rbind(cpp_mult_3000, cpp_line_3000)
data2 <- melt(data2[,c('N', 'alg', 'gflops', 'ratioL1', 'ratioL2')], id=c('N', 'alg', 'gflops'))
names(data2)[names(data2) == 'variable'] <- 'cacheType'
names(data2)[names(data2) == 'value'] <- 'cacheValue'
data2$cacheType <- ifelse(data2$cacheType == "ratioL1", "L1", "L2")

# 2.1 - Cache faults
p2.1 <- ggplot(data = filter(data2, alg == "Alg 1"), aes(x=N, y=cacheValue, colour=paste(alg, cacheType))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="Data cache miss rate (%)") +
  scale_color_discrete(name=NULL) +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"), legend.justification=c(1,0.5), legend.position=c(1,0.5))
ggsave("plot2_1.pdf", width=4, height=3)

p2.2 <- ggplot(data = filter(data2, alg == "Alg 2"), aes(x=N, y=cacheValue, colour=paste(alg, cacheType))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="Data cache miss rate (%)") +
  scale_color_discrete(name=NULL) +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"), legend.justification=c(1,0.5), legend.position=c(1,0.5))
ggsave("plot2_2.pdf", width=4, height=3)

# 2.3 - For values larger than 3000:
data2.3 <- rbind(cpp_line_3000, cpp_line_10000)
data2.3 <- melt(data2.3[,c('N', 'alg', 'gflops', 'ratioL1', 'ratioL2')], id=c('N', 'alg', 'gflops'))
names(data2.3)[names(data2.3) == 'variable'] <- 'cacheType'
names(data2.3)[names(data2.3) == 'value'] <- 'cacheValue'
data2.3$cacheType <- ifelse(data2.3$cacheType == "ratioL1", "L1", "L2")

p2.3 <- ggplot(data = data2.3, aes(x=N, y=cacheValue, colour=paste(alg, cacheType))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="Data cache miss rate (%)") +
  scale_color_discrete(name=NULL) +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"), legend.justification=c(1,0.5), legend.position=c(1,0.5))
ggsave("plot2_3.pdf", width=4, height=3)

# 2.4 - GFLOPs for values larger than 3000
p2.4 <- ggplot(data = data2.3, aes(x=N, y=gflops, color=alg)) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="GFLOP/s") +
  scale_color_discrete(name=NULL) +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"), legend.justification=c(1,0.5), legend.position=c(1,0.5))
ggsave("plot2_4.pdf", width=4, height=3)

# 3 - Parallel Stuff
data3 <- rbind(cpp_mult_par, cpp_line_par)

# 3.1 - GLOPs
p3.1 <- ggplot(data = filter(data3), aes(x=N, y=gflops, group=paste(alg,threads), color=factor(threads), alpha=alg)) +
  scale_alpha_discrete(range = c(1.0, 0.4)) +
  geom_point(aes(type=alg)) + geom_line(aes(linetype=alg)) +
  labs(x="Tamanho da matriz", y="GFLOPs") +
  scale_color_discrete(name="Número de threads") +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"))
ggsave("plot3_1.pdf", width=9, height=3)
p3.1

# 3.2 - Melhoria nos GLOPs
data3$improv <- 0.0

getImprovement <- function(alg, N)
{
  dataOriginal <- rbind(cpp_mult_3000, cpp_line_3000)
  data3[data3$alg == alg & data3$N == N, ]$improv <<- 
    data3[data3$alg == alg & data3$N == N, ]$gflops / 
    dataOriginal[dataOriginal$alg == alg & dataOriginal$N == N,]$gflops
}

getImprovement("Alg 1", 600)
getImprovement("Alg 1", 1000)
getImprovement("Alg 1", 1400)
getImprovement("Alg 1", 1800)
getImprovement("Alg 1", 2200)
getImprovement("Alg 1", 2600)
getImprovement("Alg 1", 3000)

getImprovement("Alg 2", 600)
getImprovement("Alg 2", 1000)
getImprovement("Alg 2", 1400)
getImprovement("Alg 2", 1800)
getImprovement("Alg 2", 2200)
getImprovement("Alg 2", 2600)
getImprovement("Alg 2", 3000)

# Alg1
p3.2 <- ggplot(data = filter(data3, alg == "Alg 1"), aes(x=N, y=improv, color=factor(threads))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="Improvement") +
  scale_color_discrete(name="Número de threads") +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"))
ggsave("plot3_2.pdf", width=4, height=3)
p3.2

# Alg2
p3.3 <- ggplot(data = filter(data3, alg == "Alg 2"), aes(x=N, y=improv, color=factor(threads))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="Improvement") +
  scale_color_discrete(name="Número de threads") +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"))
ggsave("plot3_3.pdf", width=4, height=3)
p3.3

# Cache faults
data3 <- melt(data3[,c('N', 'alg', 'gflops', 'threads', 'ratioL1', 'ratioL2')], id=c('N', 'alg', 'gflops', 'threads'))
names(data3)[names(data3) == 'variable'] <- 'cacheType'
names(data3)[names(data3) == 'value'] <- 'cacheValue'
data3$cacheType <- ifelse(data3$cacheType == "ratioL1", "L1", "L2")

p3.4 <- ggplot(data = filter(data3, alg == "Alg 1" & cacheType == "L1"), aes(x=N, y=cacheValue, colour=paste(threads, cacheType))) +
  geom_point(alpha=0.75) + geom_line(alpha=0.75) +
  labs(x="Tamanho da matriz", y="Faults") +
  scale_color_discrete(name=NULL) +
  theme(plot.margin=unit(c(0.1,0.1,0.1,0.1), "cm"))
ggsave("plot3_4.pdf", width=9, height=9)
p3.4


# Ver um gráfico em cima do outro:
# grid.newpage()
# grid.draw(rbind(ggplotGrob(plot1.1), ggplotGrob(plot1.2), size = "last"))
